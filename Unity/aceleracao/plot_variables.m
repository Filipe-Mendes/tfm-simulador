%% Replace commmas with dots
comma2point_overwrite('log_position.txt');
comma2point_overwrite('log_acceleration.txt');
comma2point_overwrite('log_velocity.txt');
comma2point_overwrite('log_rotation.txt');

%% Read log files
position = load('log_position.txt');
velocity = load('log_velocity.txt');
acceleration = load('log_acceleration.txt');
rotation = load('log_rotation.txt');

t = 1;
x = 2;
y = 3;
z = 4;

max_y = ceil(1.05*(max([max(position(:,x:z), [], 'all'), max(velocity(:,x:z), [], 'all'), max(acceleration(:,x:z), [], 'all')])));
min_y = floor(1.05*(min([min(position(:,x:z), [], 'all'), min(velocity(:,x:z), [], 'all'), min(acceleration(:,x:z), [], 'all')])));

%% X
figure('name','X');
x1 = plot(position(:,t),position(:,x)); LX1 = "Position.x";
hold on
x2 = plot(position(:,t),velocity(:,x)); LX2 = "Velocity.x";
x3 = plot(position(:,t),acceleration(:,x)); LX3 = "Acceleration.x";
hold off
legend([x1,x2,x3], [LX1, LX2, LX3]);
xlabel('Time')
ylabel('X value')
ylim([min_y max_y])
title('X value / Time')

%% Y
figure('name','Y');
y1 = plot(position(:,t),position(:,y)); LY1 = "Position.y";
hold on
y2 = plot(position(:,t),velocity(:,y)); LY2 = "Velocity.y";
y3 = plot(position(:,t),acceleration(:,y)); LY3 = "Acceleration.y";
hold off
legend([y1,y2,y3], [LY1, LY2, LY3]);
xlabel('Time')
ylabel('Y value')
ylim([min_y max_y])
title('Y value / Time')

%% Z
figure('name','Z');
z1 = plot(position(:,t),position(:,z)); LZ1 = "Position.z";
hold on
z2 = plot(position(:,t),velocity(:,z)); LZ2 = "Velocity.z";
z3 = plot(position(:,t),acceleration(:,z)); LZ3 = "Acceleration.z";
hold off
legend([z1,z2,z3], [LZ1, LZ2, LZ3]);
xlabel('Time')
ylabel('Z value')
ylim([min_y max_y])
title('Z value / Time')
