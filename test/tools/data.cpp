//
// Created by Miha Röthl on 20/08/2017.
//

#include "data.h"
#include "../../src/controller.h"


using namespace std;


vector<Measurement> Data::GenerateApproachingTraffic() {

  vector<Measurement> trafic_measurements;

  trafic_measurements.push_back(Measurement(   0, 1384.73 , 1178.154, 10.98248, -1.042714, 610.1682, 5.979259));
  trafic_measurements.push_back(Measurement(   1, 1228.477, 1188.592, 19.84602,  0.652741, 452.6711, 5.956659));
  trafic_measurements.push_back(Measurement(   2, 1329.12 , 1179.68 , 14.59342, -1.723392, 554.8099, 9.833732));
  trafic_measurements.push_back(Measurement(   3, 1331.735, 1183.453, 16.75315, -2.094305, 556.9899, 5.794362));
  trafic_measurements.push_back(Measurement(   4, 1168.479, 1186.078, 18.51955,  1.003577, 392.54  , 5.929722));
  trafic_measurements.push_back(Measurement(   5, 1120.858, 1182.724, 19.53747,  1.823071, 344.3234, 5.528574));
  trafic_measurements.push_back(Measurement(   6, 9999.999, 9999.999, 14.79066,-0.7870631, 829.9634, 2.023912));
  trafic_measurements.push_back(Measurement(   7, 1410.518, 1175.312, 17.96696, -2.225884, 636.3141, 5.874688));
  trafic_measurements.push_back(Measurement(   8, 9999.999, 9999.999, 14.80411, -1.951285, 862.0803, 1.845128));
  trafic_measurements.push_back(Measurement(   9, 1207.982, 1191.795, 20.75617,  0.922533, 432.2708, 2.057689));
  trafic_measurements.push_back(Measurement(  10, 1225.337, 1184.475, 21.03229,  0.722437, 449.3939, 9.965386));
  trafic_measurements.push_back(Measurement(  11, 1305.734, 1182.008, 14.43281, -1.044069, 530.6415, 10.08663));

  return trafic_measurements;
}

Measurement Data::GenerageEgoMeasurement()
{
  return Measurement(-100, 1284.63 , 1187.22 , 22.0218 , -0.799344, 530.087 , 5.83056 );
}



vector<Measurement> Data::GenerateCase5FollowingTraffic() {

  vector<Measurement> trafic_measurements;

  trafic_measurements.push_back(Measurement(   0, 1384.73 , 1178.154, 10.98248, -1.042714, 555.1682, 1.979259));

  return trafic_measurements;
}

Measurement Data::GenerageCase5FollowingEgo()
{
  return Measurement(-100, 1284.63 , 1187.22 , 22.0218 , -0.799344, 530.087 , 1.83056 );
}



Vehicle Data::GenerateVehicleInTheMiddleLaneOfTheEmptyRoad() {

  //      L   M   R
  //   ||   |   |   ||
  //   ||   | V |   ||
  //   ||   |   |   ||

  Controller *controller = new Controller(kMiddleLane);
  Machine *machine = new Machine(controller);

  Vehicle vehicle(machine);
  machine->Cruise(&vehicle);

  auto ego = EgoInTheMiddleLane();
  auto traffic = TrafficNoTraffic();

  vehicle.UpdateEgoData(ego);
  vehicle.UpdateTrafficData(traffic);

  return vehicle;
}

Vehicle Data::GenerateVehicleInTheLeftLaneOfTheEmptyRoad() {

  //      L   M   R
  //   ||   |   |   ||
  //   || V |   |   ||
  //   ||   |   |   ||

  Controller *controller = new Controller(kLeftLane);
  Machine *machine = new Machine(controller);

  Vehicle vehicle(machine);
  machine->Cruise(&vehicle);

  auto ego = EgoInLeftLane();
  auto traffic = TrafficNoTraffic();

  vehicle.UpdateEgoData(ego);
  vehicle.UpdateTrafficData(traffic);

  return vehicle;
}

Vehicle Data::GenerateVehicleInTheMiddleLaneFollowingTraffic() {

  //      L   M   R
  //   ||   |   |   ||
  //   ||   | 8 |   ||
  //   ||   |   |   ||
  //   ||   | V |   ||
  //   ||   |   |   ||

  Controller *controller = new Controller(kLeftLane);
  Machine *machine = new Machine(controller);

  Vehicle vehicle(machine);
  machine->Cruise(&vehicle);
  machine->Follow(&vehicle);

  auto ego = EgoInTheMiddleLane();
  auto traffic = TrafficInTheMiddleLaneAhead();

  vehicle.UpdateEgoData(ego);
  vehicle.UpdateTrafficData(traffic);

  return vehicle;
}

Vehicle Data::GenerateVehicleInTheMiddleLaneFollowingTrafficAndTrafficOnTheLeftAhead() {
  //      L   M   R
  //   ||   |   |   ||
  //   || 7 | 8 |   ||
  //   ||   |   |   ||
  //   ||   | V |   ||
  //   ||   |   |   ||

  Controller *controller = new Controller(kMiddleLane);
  Machine *machine = new Machine(controller);

  Vehicle vehicle(machine);
  machine->Cruise(&vehicle);
  machine->Follow(&vehicle);

  auto ego = EgoInTheMiddleLane();
  auto traffic = TrafficInTheLeftAndTheMiddleLaneAhead();

  vehicle.UpdateEgoData(ego);
  vehicle.UpdateTrafficData(traffic);

  return vehicle;
}

Vehicle Data::GenerateVehicleInTheMiddleLaneFollowingTrafficAndTrafficOnTheLeftAndRightAhead() {
  //      L   M   R
  //   ||   |   |   ||
  //   || 7 | 8 | 9 ||
  //   ||   |   |   ||
  //   ||   | V |   ||
  //   ||   |   |   ||

  Controller *controller = new Controller(kMiddleLane);
  Machine *machine = new Machine(controller);

  Vehicle vehicle(machine);
  machine->Cruise(&vehicle);
  machine->Follow(&vehicle);

  auto ego = EgoInTheMiddleLane();
  auto traffic = TrafficInAllLanesAhead();

  vehicle.UpdateEgoData(ego);
  vehicle.UpdateTrafficData(traffic);

  return vehicle;

}

Measurement* Data::EgoInTheMiddleLane()
{
  return new Measurement(-100, 0. , 0. , 15. , 0., 100. , 6.00005 );
}

Measurement* Data::EgoInLeftLane() {
  return new Measurement(-100, 0. , 0. , 15. , 0., 100. , 2.00005 );
}

vector<Measurement> Data::TrafficNoTraffic()
{
  vector<Measurement> traffic;
  return traffic;
}

std::vector<Measurement> Data::TrafficInTheMiddleLaneAhead() {

  vector<Measurement> traffic;
  traffic.push_back(Measurement( 8, 0. , 0. , 15. , 0., 120. , 6. ));

  return traffic;
}

std::vector<Measurement> Data::TrafficInTheLeftAndTheMiddleLaneAhead() {

  vector<Measurement> traffic;
  traffic.push_back(Measurement( 7, 0. , 0. , 15. , 0., 120. , 2. ));
  traffic.push_back(Measurement( 8, 0. , 0. , 15. , 0., 120. , 6. ));

  return traffic;
}

std::vector<Measurement> Data::TrafficInAllLanesAhead() {

  vector<Measurement> traffic;
  traffic.push_back(Measurement( 7, 0. , 0. , 15. , 0., 120. , 2. ));
  traffic.push_back(Measurement( 8, 0. , 0. , 15. , 0., 120. , 6. ));
  traffic.push_back(Measurement( 8, 0. , 0. , 15. , 0., 120. , 10. ));

  return traffic;
}

