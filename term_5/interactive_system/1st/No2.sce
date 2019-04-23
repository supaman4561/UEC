m = 1.0; //weight
k = 1.0; //spring constant
c = 1.0; //damper constant
x = 1.0; //location 
v = 0; //velocity
dt = 0.1; //delta
record = []; 
for time = 0:dt:10
    F = -k * x + (-c) * v;
    a = F / m;
    v = v + a * dt;
    x = x + v * dt;
    record = [record, x];
end
plot([0:dt:10], record);
