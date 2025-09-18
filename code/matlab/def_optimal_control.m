%%
%             Agent Logic
%       Optimal Control Solution
%                2024
%
%%
clear; clc; close all

%% Plant equations
syms s(t) v(t) a(t) u(t) l1(t) l2(t) l3(t);
ode1 = diff(s) == v;
ode2 = diff(v) == a;
ode3 = diff(a) == u;

%% Cost function inside the integral
L = u^2;

%% Hamiltonian
H = L + l1*rhs(ode1) + l2*rhs(ode2) + l3*rhs(ode3);
% - rhs() gets the right hand side

%% Solving the Hamiltonian
du = functionalDerivative(H,u);
syms opt_u;
opt_u = solve(subs(du,u(t),opt_u)==0,opt_u);
% opt_u = solve(functionalDerivative(H,u) == 0, u);

%% Second Optimality Condition
Dl1 = diff(l1,t)==-functionalDerivative(H,s);
Dl2 = diff(l2,t)==-functionalDerivative(H,v);
Dl3 = diff(l3,t)==-functionalDerivative(H,a);

%% Substitute u to state equations
ode3s = diff(a) == subs(rhs(ode3), u, opt_u);
% ode3s = subs(ode3, u, opt_u);

%% Boundary condition on initial and final states  
ICs = 's(0)=0, v(0)=v0, a(0)=a0';
FCs = 's(T)=sf, v(T)=vf, a(T)=af'; 

%% Find the solution of the OCP imposing the boundary condition
sol_opt = dsolve([ode1,ode2,ode3s,Dl1,Dl2,Dl3],ICs, FCs);

disp('Optimal polynomial longitudinal position:');
pretty(sol_opt.s)

disp('Optimal polynomial velocity:');
pretty(sol_opt.v)

disp('Optimal polynomial acceleration:');
pretty(sol_opt.a)

%% Assign to functions the solutions found

%% Obtain optimal control solution
sol_opt.j = subs(opt_u,l3(t),sol_opt.l3);

%% Export the solution in a matlab function
syms t v0 a0 sf vf af T             
s_opt_fun = matlabFunction(sol_opt.s,'Vars',[t,v0,a0,sf,vf,af,T],'File','s_opt.m');
v_opt_fun = matlabFunction(sol_opt.v,'Vars',[t,v0,a0,sf,vf,af,T],'File','v_opt.m');
a_opt_fun = matlabFunction(sol_opt.a,'Vars',[t,v0,a0,sf,vf,af,T],'File','a_opt.m');
j_opt_fun = matlabFunction(sol_opt.j,'Vars',[t,v0,a0,sf,vf,af,T],'File','j_opt.m');

%coeffs_sfun = @(t,coeffs) coeffs(1)+1*coeffs(2).*t+1/2*coeffs(3).*t.^2+1/6*coeffs(4).*t.^3+1/24*coeffs(5).*t.^4+1/120*coeffs(6).*t.^5;
%coeffs_vfun = @(t,coeffs) coeffs(2)+1*coeffs(3).*t+1/2*coeffs(4).*t.^2+1/6*coeffs(5).*t.^3+1/24*coeffs(6).*t.^4;
%coeffs_afun = @(t,coeffs) coeffs(3)+1*coeffs(4).*t+1/2*coeffs(5).*t.^2+1/6*coeffs(6).*t.^3;
%coeffs_jfun = @(t,coeffs) coeffs(4)+1*coeffs(5).*t+1/2*coeffs(6).*t.^2;

%% Export the coefficent list in a matlab function
% the coeffs are moltiplied by [1,2,6,24,120] to obtain the value of c1, c2, c3, c4, c5
coef_list_var = [0,coeffs(sol_opt.s,t) .* [1,2,6,24,120]];
coef_list_fun = matlabFunction(coef_list_var,'Vars',[v0,a0,sf,vf,af,T],'File','coef_list.m');

%% Export the total cost in a matlab function 
total_cost_var = simplify(int(sol_opt.j^2,t,0,T));
total_cost_fun = matlabFunction(total_cost_var,'Vars',[v0,a0,sf,vf,af,T],'File','total_cost.m');

%% Inspect solutions  

Tmax  = 20.;
t_list = linspace(0,Tmax,100);

v0val = 10;
a0val = 0;
xfval = 90;
vfval = 0.;
afval = 0.;

%% The functions work both for vector (t_list) or number (t)
s_list = s_opt_fun(t_list, v0val, a0val, xfval, vfval, afval, Tmax);
v_list = v_opt_fun(t_list, v0val, a0val, xfval, vfval, afval, Tmax);
a_list = a_opt_fun(t_list, v0val, a0val, xfval, vfval, afval, Tmax);
j_list = j_opt_fun(t_list, v0val, a0val, xfval, vfval, afval, Tmax);

figure(1)
%% Position    
subplot(2,4,1)
plot(t_list, s_list)
grid on
xlabel('Time (s)','Interpreter','latex');
ylabel('Position $(m)$','Interpreter','latex');
    
%% Velocity
subplot(2,4,2)
plot(t_list, v_list)
grid on
xlabel('Time (s)','Interpreter','latex'),
ylabel('Velocity $(\frac{m}{s})$','Interpreter','latex'),
    
%% Acceleration
subplot(2,4,3)
plot(t_list, a_list)
grid on
xlabel('Time (s)','Interpreter','latex'),
ylabel('Acceleration $(\frac{m}{s^2})$','Interpreter','latex'),

%% Control
subplot(2,4,4)
plot(t_list, j_list)
grid on
xlabel('Time (s)','Interpreter','latex'),
ylabel('Control $(\frac{m}{s^3})$','Interpreter','latex')
    
%% Velocity on position
subplot(2,4,6)
plot(s_list, v_list)
grid on
xlabel('Position (m)','Interpreter','latex'),
ylabel('Velocity $(\frac{m}{s})$','Interpreter','latex'),
    
%% Acceleration on position
subplot(2,4,7)
plot(s_list, a_list)
grid on
xlabel('Position (m)','Interpreter','latex'),
ylabel('Acceleration $(\frac{m}{s^2})$','Interpreter','latex'),

% Control on position
subplot(2,4,8)
plot(s_list, j_list)
grid on
xlabel('Position (m)','Interpreter','latex'),
ylabel('Control $(\frac{m}{s^3})$','Interpreter','latex')

