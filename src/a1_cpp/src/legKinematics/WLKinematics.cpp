//
// Created by zixin on 7/8/22.
//

#include "WLKinematics.h"

Eigen::Vector3d WLKinematics::fk(Eigen::Vector3d q, Eigen::VectorXd rho_fix) {
    Eigen::Vector3d out;
    autoFunc_fk_derive(q.data(), rho_fix.data(), out.data());
    return out;
}

Eigen::Matrix3d WLKinematics::jac(Eigen::Vector3d q, Eigen::VectorXd rho_fix) {
    Eigen::Matrix3d mtx;
    autoFunc_d_fk_dtheta(q.data(), rho_fix.data(), mtx.data());
    return mtx;
}

// functions generated by matlab
void WLKinematics::autoFunc_fk_derive(const double theta[3], const double rho_fix[5], double foot_pos[3]) {
    double d = rho_fix[2];
    double lc = rho_fix[4];
    double lt = rho_fix[3];
    double ox = rho_fix[0];
    double oy = rho_fix[1];
    double t1 = theta[0];
    double t2 = theta[1];
    double t3 = theta[2];

    double t5 = std::cos(t1);
    double t6 = std::cos(t2);
    double t7 = std::cos(t3);
    double t8 = std::sin(t1);
    double t9 = std::sin(t2);
    double t10 = std::sin(t3);

    foot_pos[0] = ox + lt * t9 + lc * std::sin(t2 + t3);
    foot_pos[1] = oy + d * t5 + lt * t6 * t8 + lc * t6 * t7 * t8 - lc * t8 * t9 * t10;
    foot_pos[2] = d * t8 - lt * t5 * t6 - lc * t5 * t6 * t7 + lc * t5 * t9 * t10;
}

void WLKinematics::autoFunc_d_fk_dtheta(const double theta[3], const double rho_fix[5], double jacobian[9]) {
    double d = rho_fix[2];
    double lc = rho_fix[4];
    double lt = rho_fix[3];
    double t1 = theta[0];
    double t2 = theta[1];
    double t3 = theta[2];

    double t5 = std::cos(t1);
    double t6 = std::cos(t2);
    double t7 = std::cos(t3);
    double t8 = std::sin(t1);
    double t9 = std::sin(t2);
    double t10 = std::sin(t3);
    double t11 = t2 + t3;
    double t12 = std::cos(t11);
    double t13 = lt*t9;
    double t14 = std::sin(t11);
    double t15 = lc*t12;
    double t16 = lc*t14;
    double t17 = t13 + t16;

    jacobian[0] = 0.0;
    jacobian[1] = -d*t8 + lt*t5*t6 + lc*t5*t6*t7 - lc*t5*t9*t10;
    jacobian[2] = d*t5 + lt*t6*t8 + lc*t6*t7*t8 - lc*t8*t9*t10;

    jacobian[3] = t15 + lt*t6;
    jacobian[4] = -t8*t17;
    jacobian[5] = t5*t17;

    jacobian[6] = t15;
    jacobian[7] = -t8*t16;
    jacobian[8] = t5*t16;
}