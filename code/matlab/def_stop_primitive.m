%%
%           Agent Logic
%         Stop Primitive
%              2024
%
%
%% Stop primitive %%
syms z; % We create this variable for more stable solution of the equations

%% Determine the optimal time to stop %%
final_opt_time_stop_var = 1./solve(diff(subs(total_cost_var,[vf,af,T],[0,0,1/z]),z)==0,z);

%% Export the solution in a matlab function %%
final_opt_time_stop_fun = matlabFunction(final_opt_time_stop_var(1),'Vars',[v0,a0,sf],'File','final_opt_time_stop.m');
