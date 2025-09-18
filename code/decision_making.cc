//
// Created by Gastone Pietro Rosati Papini on 10/08/22.
// Modified by Murgia Edoardo in 2024
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <algorithm>

extern "C" {
#include "screen_print_c.h"
}
#include "screen_print.h"
#include "server_lib.h"
#include "logvars.h"

// --- MATLAB PRIMITIVES INCLUDE ---
#include "primitives.h"
// --- MATLAB PRIMITIVES INCLUDE ---

#define DEFAULT_SERVER_IP    "127.0.0.1"
#define SERVER_PORT               30000  // Server port
#define DT 0.05

// Handler for CTRL-C
#include <signal.h>
static uint32_t server_run = 1;
void intHandler(int signal) {
    server_run = 0;
}

bool isempty(const double vec[6]) {
    for (int i = 0; i < 6; ++i) {
        if (vec[i] != 0.0) {
            return false;
        }
    }
    return true;
}

int main(int argc, const char * argv[]) {
    logger.enable(true);

    // Messages variables
    scenario_msg_t scenario_msg;
    manoeuvre_msg_t manoeuvre_msg;
    size_t scenario_msg_size = sizeof(scenario_msg.data_buffer);
    size_t manoeuvre_msg_size = sizeof(manoeuvre_msg.data_buffer);
    uint32_t message_id = 0;

#if not defined( _MSC_VER ) and not defined( _WIN32 )
    // More portable way of supporting signals on UNIX
    struct sigaction act;
    act.sa_handler = intHandler;
    sigaction(SIGINT, &act, NULL);
#else
    signal(SIGINT, intHandler);
#endif

    server_agent_init(DEFAULT_SERVER_IP, SERVER_PORT);

    // Start server of the Agent
    printLine();
    printTable("Waiting for scenario message...", 0);
    printLine();
    while (server_run == 1) {

        // Clean the buffer
        memset(scenario_msg.data_buffer, '\0', scenario_msg_size);

        // Receive scenario message from the environment
        if (server_receive_from_client(&server_run, &message_id, &scenario_msg.data_struct) == 0) {
            // Init time
            static auto start = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::now()-start;
            double num_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(time).count()/1000.0;
            printLogTitle(message_id, "received message");

            // Data struct
            input_data_str *in = &scenario_msg.data_struct;
            manoeuvre_msg.data_struct.CycleNumber = in->CycleNumber;
            manoeuvre_msg.data_struct.Status = in->Status;


            // -------------------------------------------------------------------------------------------------------


            // VARIABLES USED BY THE PROGRAM -------------------------------------------------------------------------

            static double init_dist = in->TrfLightDist;
            double vmin = 3.0;
            double vmax = 10.0;
            double amin = -10.0;
            double amax = 5.0;
            double v0 = in->VLgtFild;
            double a0 = fmin(fmax(in->ALgtFild, amin), amax);
            double vr = in->RequestedCruisingSpeed;
            double xs = 5.0;
            double Ts = xs/vmin;
            double xin = 10.0;
            double Tin = xin/vmin;
            double xtr, xstop;
            double m1[6];
            double m2[6];
            double bestm[6];
            double lookhead = fmax(50, v0*5);  // Maximum sensing distance of the vehicle
            double v1, v2;
            double T1, T2;
            double Tgreen, Tred;
            double s1;
            static double vbest;
            // If the traffic light is too far and the vehicle can't sense it, the velocity to reach is the maximum one:
            #define freeflow(v0, a0, xf, vr) pass_primitive(v0, a0, xf, vr, vr, 0, 0, m2, &v2, &T2, m1, &v1, &T1);
            if (v0 > vbest) vbest = v0;  // Created out of curiosity, not useful for the functioning of the program

            // VARIABLES USED BY THE PROGRAM -------------------------------------------------------------------------


            // -------------------------------------------------------------------------------------------------------


            // PRIMITIVES VISUALIZATION: -----------------------------------------------------------------------------
            /*
            if (in->TrfLightDist < 80.0) {
                stop_primitive(v0, a0, in->TrfLightDist, m1, &s1, &T1);
            } else {
                freeflow(v0, a0, in->TrfLightDist, vr);
            }
            memcpy(bestm, m1, sizeof(m1));
            */
            // PRIMITIVES VISUALIZATION: -----------------------------------------------------------------------------
            // UNCOMMENT THIS TO VISUALIZE PRIMITIVES IN MATLAB VIA FILE "vis_primitives.m" CONTAINED IN FOLDER:
            // '/basic_agent_st/bin/log_internal'


            // -------------------------------------------------------------------------------------------------------


            // TRAFFIC LIGHT SURFER: ---------------------------------------------------------------------------------

            if (in->NrTrfLights != 0) {
                xtr = in->TrfLightDist;
                xstop = in->TrfLightDist - xs/2;
            }
            if (in->NrTrfLights == 0 || xtr > lookhead || in->TrfLightDist < 0.0) {
                freeflow(v0, a0, lookhead, vr);
                memcpy(bestm, m1, sizeof(m1));
                std::cout << "Free Flowing cause far from the trafficlight"  << std::endl;
            } else {
                switch (in->TrfLightCurrState) {
                    case 1:
                        Tgreen = 0;
                        Tred = in->TrfLightFirstTimeToChange - Tin;
                        std::cout << "TrfLght GREEN" << std::endl;
                        break;
                    case 2:
                        Tgreen = in->TrfLightSecondTimeToChange + Ts;
                        Tred = in->TrfLightThirdTimeToChange - Tin;
                        std::cout << "TrfLght YELLOW" << std::endl;
                        break;
                    case 3:
                        Tgreen = in->TrfLightFirstTimeToChange + Ts;
                        Tred = in->TrfLightSecondTimeToChange - Tin;
                        std::cout << "TrfLght RED" << std::endl;
                        break;
                }
                if (in->TrfLightCurrState == 1 && in->TrfLightDist <= xs) {
                    freeflow(v0, a0, lookhead, vr);
                    memcpy(bestm, m1, sizeof(m1));
                    std::cout << "Free Flowing because near to the trafficlight"  << std::endl;
                } else {
                    pass_primitive(v0, a0, xtr, vmin, vmax, Tgreen, Tred, m2, &v2, &T2, m1, &v1, &T1);
                    if (isempty(m1) && isempty(m2)) {
                        stop_primitive(v0, a0, xstop, m1, &s1, &T1);
                        std::cout << "Stopping" << std::endl;
                        memcpy(bestm, m1, sizeof(m1));
                    } else {
                        if ((m1[3] < 0 && m2[3] > 0) || (m1[3] > 0 && m2[3] < 0)) {
                            pass_primitive_j0(v0, a0, xtr, vmin, vmax, m1, &v1, &T1);
                            memcpy(bestm, m1, sizeof(m1));
                            std::cout << "Passing using J0" << std::endl;
                        } else {
                            if (abs(m1[3]) < abs(m2[3])) {
                                memcpy(bestm, m1, sizeof(m1));
                                std::cout << "Passing  using M1" << std::endl;
                            } else {
                                memcpy(bestm, m2, sizeof(m2));
                                std::cout << "Passing using M2" << std::endl;
                            }
                        }
                    }
                }
            }

            // TRAFFIC LIGHT SURFER: ---------------------------------------------------------------------------------
            // COMMENT THE SECTION ABOVE TO VISUALIZE THE PRIMITIVES, UNCOMMENTING THE APPOSITE SECTION BEFORE


            // -------------------------------------------------------------------------------------------------------


            // LOW LEVEL CONTROL -------------------------------------------------------------------------------------

            static double eint = 0.0;
            double Pgain = 0.1;
            double Igain = 1.0;
            double jEval0 = bestm[3];
            double jEvaldt = bestm[3] + bestm[4] * DT + 0.5 * bestm[5] * DT * DT;
            static double a0_bar = a0;
            double areq = a0_bar + DT/2.0 * (jEval0 + jEvaldt);
            areq = fmin(fmax(areq, amin), amax);
            a0_bar = areq;

            if (v0 < 0.1) { // Anti - Windup : if the velocity is nearly zero, the integral error is imposed to zero too.
                eint = 0.0;
            }

            double e = areq - a0;
            eint += e * DT;

            double ReqPed = e * Pgain + eint * Igain;

            manoeuvre_msg.data_struct.RequestedAcc = ReqPed;
            manoeuvre_msg.data_struct.RequestedSteerWhlAg = 0.0;

            // LOW LEVEL CONTROL -------------------------------------------------------------------------------------


            // -------------------------------------------------------------------------------------------------------


            // DATA PRINTED ON TERMINAL ------------------------------------------------------------------------------

            std::cout << std::endl;
            std::cout << "Distanza: " << in->TrfLightDist << std::endl; // Distance to  the trafficlight
            std::cout << "Velocità: " << v0 << std::endl;               // Velocity of the vehicle
            std::cout << "A_zero  : " << a0 << std::endl;               // Acceleration of the vehicle
            std::cout << "A_req   : " << areq << std::endl;             // Requested acceleration
            std::cout << "Error   : " << eint << std::endl;             // PID error
            std::cout << "Maximum velocity: " << vbest << std::endl;    // Maximum velocity of the vehicle
            std::cout << std::endl;
            
            // DATA PRINTED ON TERMINAL ------------------------------------------------------------------------------


            // -------------------------------------------------------------------------------------------------------


            // DATA SENT TO MATLAB  ----------------------------------------------------------------------------------

            logger.log_var("logout", "cycle", in->CycleNumber);
            logger.log_var("logout", "time", in->ECUupTime);
            logger.log_var("logout", "dist", init_dist - in->TrfLightDist);
            logger.log_var("logout", "vel", v0);
            logger.log_var("logout", "acc", a0);
            logger.log_var("logout", "req_acc", areq);
            logger.log_var("logout", "req_ped", ReqPed);
            logger.log_var("logout", "req_vel", vr);

            logger.log_var("logout", "C0", bestm[0]);
            logger.log_var("logout", "C1", bestm[1]);
            logger.log_var("logout", "C2", bestm[2]);
            logger.log_var("logout", "C3", bestm[3]);
            logger.log_var("logout", "C4", bestm[4]);
            logger.log_var("logout", "C5", bestm[5]);
            logger.log_var("logout", "bestT", T1);

            logger.write_line("logout");

            // DATA SENT TO MATLAB  ----------------------------------------------------------------------------------


            // -------------------------------------------------------------------------------------------------------


            // SEND MANOEUVRE MESSAGE TO THE ENVIRONMENT -------------------------------------------------------------

            if (server_send_to_client(server_run, message_id, &manoeuvre_msg.data_struct) == -1) {
                perror("error send_message()");
                exit(EXIT_FAILURE);
            } else {
                printLogTitle(message_id, "sent message");
            }

            // SEND MANOEUVRE MESSAGE TO THE ENVIRONMENT -------------------------------------------------------------

        }
    }

    // CLOSE THE SERVER OF THE AGENT ---------------------------------------------------------------------------------

    server_agent_close();
    return 0;
}