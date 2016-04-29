#include <QtSerialPort/QtSerialPort>
#include <QtWidgets/QApplication>
#include <QString>
#include <iostream>
#include <cmath>
#include <functional>
#include <algorithm>
#include <array>

#include <unistd.h>
#include <sys/time.h>

#include <cereal/types/vector.hpp>

#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>

#include <zmq.hpp>

#include <messages/servo_action.hpp>
#include <messages/endpoint_action.hpp>
#include <messages/optoforce_data.hpp>

#include <filter/average.hpp>
#include <filter/limiter.hpp>
#include <filter/integral.hpp>
#include <filter/derivate.hpp>

using namespace std;

template<typename T>
void send(zmq::socket_t& sock_pub, T& ea) {
  stringstream oss;

  {
    cereal::BinaryOutputArchive ar(oss);
    ar(ea);
  }

  zmq::message_t msg(oss.str().size());
  oss.str().copy((char*)msg.data(), msg.size());

  sock_pub.send(msg, ZMQ_NOBLOCK);
}

struct WalkConfig {
  double offset_x = -10 - 20;
  double half_esp_x = 120;

  double offset_y = 10;
  double half_esp_y = 120;

  double default_z = -180;
  double delta_z = 40;

  double period = 2;

  double step_up_ratio = 0.25;
  double move_ratio = 0.2;

  double step_size = 40;
};

struct LegConfig {
  double default_x;
  double default_y;
  double default_z;
};

double add_mod(double val, double add, double mod) {
  if(val + add > mod) {
      return val+add-mod;
    }
  return val+add;
}

double Kp2 = -0.0 / 50.0;
double Kp1 = -8.0 / 10.0;
Filter::Integral<double> avg1(0);
Filter::Integral<double> avg2(0);
Filter::Limiter<double> lim(-70, 70);

Filter::Average<double, 10> a1(0);
Filter::Derivate<double> d1(0);
Filter::Integral<double> i1(0);

void get_walk_pos_1(WalkConfig& cfg, LegConfig& leg, map<string, OptoforceData>& opto, double t, double& x, double& y, double& z) {

  double t_step1_middle = cfg.period / 4.0;
  double t_step2_middle = cfg.period * 3.0 / 4.0;

  double dt_half_step = cfg.period / 4.0;

  y = leg.default_y;

  if(abs(t - t_step1_middle) < dt_half_step * cfg.move_ratio) {
      double t2 = (t - t_step1_middle) / (dt_half_step * cfg.move_ratio);
      x = leg.default_x + t2*cfg.step_size/2.0;
    }
  else if(abs(t - t_step2_middle) < dt_half_step * cfg.move_ratio) {
      double t2 = (t - t_step2_middle) / (dt_half_step * cfg.move_ratio);
      x = leg.default_x - t2*cfg.step_size/2.0;
    }
  else if(abs(t - cfg.period/2.0) < dt_half_step) {
      x = leg.default_x + cfg.step_size/2.0;
    }
  else if(abs(t - cfg.period/2.0) > dt_half_step) {
      x = leg.default_x - cfg.step_size/2.0;
    }
  else {
      x = leg.default_x;
    }

  if(abs(t - t_step1_middle) < dt_half_step * cfg.step_up_ratio) {
      z = leg.default_z+cfg.delta_z;
    }
  else if(abs(t - t_step2_middle) < dt_half_step * cfg.step_up_ratio) {
      z = leg.default_z;
    }
  else {
      z = leg.default_z;
    }

}

void get_walk_pos_2(WalkConfig& cfg, LegConfig& leg, map<string, OptoforceData>& opto, double t, double& x, double& y, double& z) {

  double t_step1_middle = cfg.period / 4.0;
  double t_step2_middle = cfg.period * 3.0 / 4.0;

  double dt_half_step = cfg.period / 4.0;

  y = leg.default_y;

  if(abs(t - t_step1_middle) < dt_half_step * cfg.move_ratio) {
      double t2 = (t - t_step1_middle) / (dt_half_step * cfg.move_ratio);
      x = leg.default_x - t2*cfg.step_size/2.0;
    }
  else if(abs(t - t_step2_middle) < dt_half_step * cfg.move_ratio) {
      double t2 = (t - t_step2_middle) / (dt_half_step * cfg.move_ratio);
      x = leg.default_x + t2*cfg.step_size/2.0;
    }
  else if(abs(t - cfg.period/2.0) < dt_half_step) {
      x = leg.default_x - cfg.step_size/2.0;
    }
  else if(abs(t - cfg.period/2.0) > dt_half_step) {
      x = leg.default_x + cfg.step_size/2.0;
    }
  else {
      x = leg.default_x;
    }

  if(abs(t - t_step1_middle) < dt_half_step * cfg.step_up_ratio) {
      z = leg.default_z;
    }
  else if(abs(t - t_step2_middle) < dt_half_step * cfg.step_up_ratio) {
      z = leg.default_z+cfg.delta_z;
    }
  else {
      z = leg.default_z;
    }

}

void config_sock(zmq::socket_t& sock) {
  int hwm = 1;
  int linger = 0;
  sock.setsockopt(ZMQ_SNDHWM, &hwm, sizeof(hwm));
  sock.setsockopt(ZMQ_RCVHWM, &hwm, sizeof(hwm));
  sock.setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
}


void opto() {

}

int main(int, char**) {
  // IO config
  zmq::context_t ctx(5);

  zmq::socket_t sock_ik_out(ctx, ZMQ_PUB);
  sock_ik_out.connect("ipc://ik.out");

  zmq::socket_t sock_servo_out(ctx, ZMQ_PUB);
  sock_servo_out.connect("ipc://servo.out");

  zmq::socket_t sock_opto_in(ctx, ZMQ_SUB);
  sock_opto_in.connect("ipc://ik.opto.in");
  sock_opto_in.setsockopt(ZMQ_SUBSCRIBE, 0, 0);

  config_sock(sock_ik_out);
  config_sock(sock_servo_out);
  config_sock(sock_opto_in);

  WalkConfig cfg;

  LegConfig lf = {
    cfg.half_esp_x+cfg.offset_x,
    cfg.half_esp_y+cfg.offset_y,
    cfg.default_z
  };

  LegConfig rf = {
    cfg.half_esp_x+cfg.offset_x,
    -cfg.half_esp_y+cfg.offset_y,
    cfg.default_z
  };

  LegConfig lb = {
    -cfg.half_esp_x+cfg.offset_x,
    cfg.half_esp_y+cfg.offset_y,
    cfg.default_z
  };

  LegConfig rb = {
    -cfg.half_esp_x+cfg.offset_x,
    -cfg.half_esp_y+cfg.offset_y,
    cfg.default_z
  };

  double t = 0;
  double freq = 30; // hz
  struct timeval t1 = {0,0}, t2 = {0,0};

  map<string, OptoforceData> opto;

  while(1) {

      {
        zmq::message_t msg;
        if(sock_opto_in.recv(&msg, ZMQ_NOBLOCK)) {
            vector<OptoforceData> ods;

            std::stringstream ss;
            ss.write((char*)msg.data(), msg.size());

            {
              cereal::BinaryInputArchive ar(ss);
              ar(ods);
            }

            for(auto it = ods.begin() ; it != ods.end() ; it++) {
                OptoforceData& od = *it;
                opto[od.label] = od;
              }
          }
      }

      gettimeofday(&t2, NULL);
      if(abs(t2.tv_usec - t1.tv_usec) > 1000000 / freq) {
          t1.tv_sec = t2.tv_sec;
          t1.tv_usec = t2.tv_usec;

          //t = 7.5;
          t = add_mod(t, 1.0/freq, cfg.period);
          EndpointAction ea;
          vector<EndpointAction> eas;

          ea.label = "LF";
          ea.enable = true;
          get_walk_pos_1(cfg, lf, opto, t, ea.x, ea.y, ea.z);
          //send(sock_ik_out, ea);
          eas.push_back(ea);

          ea.label = "RF";
          ea.enable = true;
          get_walk_pos_2(cfg, rf, opto, t, ea.x, ea.y, ea.z);
          //send(sock_ik_out, ea);
          eas.push_back(ea);

          ea.label = "LB";
          ea.enable = true;
          get_walk_pos_2(cfg, lb, opto, t, ea.x, ea.y, ea.z);
          //send(sock_ik_out, ea);
          eas.push_back(ea);

          ea.label = "RB";
          ea.enable = true;
          get_walk_pos_1(cfg, rb, opto, t, ea.x, ea.y, ea.z);
          //send(sock_ik_out, ea);
          eas.push_back(ea);

          //cout << ea.x << " " << ea.y << " " << ea.z << endl;
          send(sock_ik_out, eas);
        }
    }

  return 0;
}
