%% Replace commmas with dots
comma2point_overwrite('log_current_velocity.txt');
comma2point_overwrite('log_acceleration.txt');
comma2point_overwrite('log_velocity.txt');

%% Read log files
current_velocity = load('log_current_velocity.txt');
velocity = load('log_velocity.txt');
acceleration = load('log_acceleration.txt');

t = 1;
x = 2;
y = 3;
z = 4;


%% Z
figure('name','Z');
z1 = plot(current_velocity(:,t),current_velocity(:,z)); LZ1 = "Current Velocity.z";
hold on
z2 = plot(current_velocity(:,t),velocity(:,z)); LZ2 = "Velocity.z";
z3 = plot(current_velocity(:,t),acceleration(:,z)); LZ3 = "Acceleration.z";
hold off
legend([z1,z2,z3], [LZ1, LZ2, LZ3]);
xlabel('Time')
ylabel('Z value')
title('Z value / Time')