%% Replace commmas with dots
comma2point_overwrite('./Assets/HardcodedAcceleration/acceleration_straight_line_drag_hardcoded.txt');


%% Read log files
acceleration = load('./Assets/HardcodedAcceleration/acceleration_straight_line_drag_hardcoded.txt');


t = 1;
x = 2;
y = 3;
z = 4;

max_y = ceil(1.05*(max(acceleration(:,x:z), [], 'all')));
min_y = floor(1.05*(min(acceleration(:,x:z), [], 'all')));

%% X
figure('name','X');
x3 = plot(acceleration(:,t),acceleration(:,x)); LX3 = "Acceleration.x";
hold off
legend(x3, LX3);
xlabel('Time')
ylabel('X value')
ylim([min_y max_y])
title('X value / Time')

%% Y
figure('name','Y');
y3 = plot(acceleration(:,t),acceleration(:,y)); LY3 = "Acceleration.y";
hold off
legend(y3, LY3);
xlabel('Time')
ylabel('Y value')
ylim([min_y max_y])
title('Y value / Time')

%% Z
figure('name','Z');
z3 = plot(acceleration(:,t),acceleration(:,z)); LZ3 = "Acceleration.z";
hold off
legend(z3, LZ3);
xlabel('Time')
ylabel('Z value')
ylim([min_y max_y])
title('Z value / Time')

