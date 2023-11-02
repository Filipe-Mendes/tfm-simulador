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

%% Position
figure('name','Position');
subplot(3,1,1);
plot(position(:,t),position(:,x))
xlabel('Time') 
ylabel('Position.x')
title('Position.x / Time')

subplot(3,1,2); 
plot(position(:,t),position(:,y))
xlabel('Time') 
ylabel('Position.y')
title('Position.y / Time')

subplot(3,1,3); 
plot(position(:,t),position(:,z))
xlabel('Time') 
ylabel('Position.z')
title('Position.z / Time')

%% Velocity
figure('name','Velocity');
subplot(3,1,1);
plot(velocity(:,t),velocity(:,x))
xlabel('Time') 
ylabel('Velocity.x')
title('Velocity.x / Time')

subplot(3,1,2); 
plot(velocity(:,t),velocity(:,y))
xlabel('Time') 
ylabel('Velocity.y')
title('Velocity.y / Time')

subplot(3,1,3); 
plot(velocity(:,t),velocity(:,z))
xlabel('Time') 
ylabel('Velocity.z')
title('Velocity.z / Time')

%% Acceleration
figure('name','Acceleration');
subplot(3,1,1);
plot(acceleration(:,t),acceleration(:,x))
xlabel('Time') 
ylabel('Acceleration.x')
title('Acceleration.x / Time')

subplot(3,1,2); 
plot(velocity(:,t),acceleration(:,y))
xlabel('Time') 
ylabel('Acceleration.y')
title('Acceleration.y / Time')

subplot(3,1,3); 
plot(velocity(:,t),acceleration(:,z))
xlabel('Time') 
ylabel('Acceleration.z')
title('Acceleration.z / Time')