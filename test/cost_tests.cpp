//
// Created by Miha Röthl on 17/08/2017.
//

#include <iostream>
#include <vector>

#include "gtest/gtest.h"

#include "../src/measurement.h"
#include "../src/vehicle.h"
#include "../src/state/states/state.h"
#include "../src/state/states/ready_state.h"
#include "../src/state/states/cruising_state.h"
#include "../src/state/states/chainging_lane_to_left_state.h"
#include "../src/state/states/chainging_lane_to_right_state.h"
#include "../src/cost.h"

#include "tools/data.h"

using namespace std;






TEST(cost, Should_CostShouldBeHigher_When_ColisionDetected)
{
  auto ego_measurement = Measurement(-100, 1284.63 , 1187.22 , 22.0218 , -0.799344, 530.087 , 5.83056 );

  Data data;

  auto trafic_measurements = data.GenerateApproachingTraffic();

  Machine machine;
  Vehicle vehicle(&machine);

  vehicle.UpdateEgoData(&ego_measurement);
  machine.Cruise(&vehicle);

  Cost cost;
  auto colision_cost = cost.ColisionCost(&vehicle, trafic_measurements);
  EXPECT_TRUE(colision_cost > 367879);


  machine.ChangeLaneToLeft(1);
  Vehicle vehicleLeft(&machine);
  colision_cost = cost.ColisionCost(&vehicleLeft, trafic_measurements);
  EXPECT_TRUE(colision_cost == 0.);
}




TEST(cost, Should_CostShouldBeHigher_When_ChaingingLanes)
{
  Data data;
  auto ego_measurement = data.GenerageEgoMeasurement();

  auto trafic_measurements = data.GenerateApproachingTraffic();

  Machine machine;
  Vehicle vehicle(&machine);

  vehicle.UpdateEgoData(&ego_measurement);

  Cost cost;
  double changeLaneCost;
  changeLaneCost = cost.ChangeLaneCost(&vehicle, trafic_measurements);
  EXPECT_EQ(changeLaneCost, 0.);

  machine.Cruise(&vehicle);
  machine.ChangeLaneToLeft(1);
  changeLaneCost = cost.ChangeLaneCost(&vehicle, trafic_measurements);
  EXPECT_EQ(changeLaneCost, cost.kComfort);
}




/*
 *
 * ---------------------------------
 car EGO ; x: 1284.63; y: 1187.22; vx: 22.0218; vy: -0.799344; s: 530.087; d: 5.83056; speed: 49.3613; yaw: 357.921
 car id: 0; x: 1384.73; y: 1178.154; vx: 10.98248; vy: -1.042714; s: 610.1682; d: 5.979259
 car id: 1; x: 1228.477; y: 1188.592; vx: 19.84602; vy: 0.652741; s: 452.6711; d: 5.956659
 car id: 2; x: 1329.12; y: 1179.68; vx: 14.59342; vy: -1.723392; s: 554.8099; d: 9.833732
 car id: 3; x: 1331.735; y: 1183.453; vx: 16.75315; vy: -2.094305; s: 556.9899; d: 5.794362
 car id: 4; x: 1168.479; y: 1186.078; vx: 18.51955; vy: 1.003577; s: 392.54; d: 5.929722
 car id: 5; x: 1120.858; y: 1182.724; vx: 19.53747; vy: 1.823071; s: 344.3234; d: 5.528574
 car id: 6; x: 1305.42; y: 1190.093; vx: 14.79066; vy: -0.7870631; s: 529.9634; d: 2.023912
 car id: 7; x: 1410.518; y: 1175.312; vx: 17.96696; vy: -2.225884; s: 636.3141; d: 5.874688
 car id: 8; x: 1337.232; y: 1186.813; vx: 14.80411; vy: -1.951285; s: 562.0803; d: 1.845128
 car id: 9; x: 1207.982; y: 1191.795; vx: 20.75617; vy: 0.9225339; s: 432.2708; d: 2.057689
 car id: 10; x: 1225.337; y: 1184.475; vx: 21.03229; vy: 0.722437; s: 449.3939; d: 9.965386
 car id: 11; x: 1305.734; y: 1182.008; vx: 14.43281; vy: -1.044069; s: 530.6415; d: 10.08663
---------------------------------
 car EGO ; x: 1285.95; y: 1187.17; vx: 22.0208; vy: -0.874591; s: 531.412; d: 5.82078; speed: 49.3654; yaw: 357.726
 car id: 0; x: 1385.333; y: 1178.097; vx: 11.19673; vy: -1.06588; s: 610.7738; d: 5.977948
 car id: 1; x: 1229.668; y: 1188.63; vx: 19.84748; vy: 0.6328186; s: 453.8626; d: 5.958306
 car id: 2; x: 1329.996; y: 1179.576; vx: 14.59256; vy: -1.735849; s: 555.6916; d: 9.83979
 car id: 3; x: 1332.74; y: 1183.326; vx: 16.7505; vy: -2.114377; s: 558.0028; d: 5.808369
 car id: 4; x: 1169.59; y: 1186.138; vx: 18.52023; vy: 0.9806107; s: 393.6526; d: 5.922825
 car id: 5; x: 1122.03; y: 1182.831; vx: 19.54295; vy: 1.759937; s: 345.4999; d: 5.573647
 car id: 6; x: 1306.224; y: 1190.049; vx: 14.78841; vy: -0.836798; s: 530.7692; d: 2.031554
 car id: 7; x: 1411.595; y: 1175.177; vx: 17.9365; vy: -2.250991; s: 637.3993; d: 5.867908
 car id: 8; x: 1338.121; y: 1186.696; vx: 14.8056; vy: -1.933327; s: 562.9762; d: 1.86226
 car id: 9; x: 1209.228; y: 1191.85; vx: 20.75487; vy: 0.9211316; s: 433.543; d: 2.050215
 car id: 10; x: 1226.599; y: 1184.518; vx: 21.03255; vy: 0.7139192; s: 450.6566; d: 9.96504
 car id: 11; x: 1306.606; y: 1181.943; vx: 14.57847; vy: -1.097386; s: 532.1837; d: 10.08391
---------------------------------
 car EGO ; x: 1286.84; y: 1187.13; vx: 22.0207; vy: -0.923365; s: 532.736; d: 5.81696; speed: 49.3697; yaw: 357.599
 car id: 0; x: 1385.721; y: 1178.06; vx: 11.33596; vy: -1.081052; s: 611.1641; d: 5.977237
 car id: 1; x: 1230.462; y: 1188.655; vx: 19.84884; vy: 0.6018332; s: 454.657; d: 5.960706
 car id: 2; x: 1330.579; y: 1179.507; vx: 14.59201; vy: -1.744037; s: 556.2795; d: 9.844275
 car id: 3; x: 1333.41; y: 1183.242; vx: 16.74963; vy: -2.12054; s: 558.678; d: 5.818331
 car id: 4; x: 1170.331; y: 1186.176; vx: 18.52063; vy: 0.9654619; s: 394.3943; d: 5.919081
 car id: 5; x: 1122.812; y: 1182.901; vx: 19.54616; vy: 1.721248; s: 346.2841; d: 5.605682
 car id: 6; x: 1306.736; y: 1190.019; vx: 14.78676; vy: -0.8711637; s: 531.2815; d: 2.037896
 car id: 7; x: 1412.311; y: 1175.087; vx: 17.91681; vy: -2.266982; s: 638.1218; d: 5.864293
 car id: 8; x: 1338.713; y: 1186.619; vx: 14.80689; vy: -1.919107; s: 563.5734; d: 1.872953
 car id: 9; x: 1210.058; y: 1191.887; vx: 20.75409; vy: 0.918463; s: 434.3739; d: 2.041512
 car id: 10; x: 1227.44; y: 1184.546; vx: 21.03273; vy: 0.7083322; s: 451.4984; d: 9.965013
 car id: 11; x: 1307.192; y: 1181.898; vx: 14.67274; vy: -1.132624; s: 532.771; d: 10.06364
---------------------------------
 car EGO ; x: 1287.72; y: 1187.1; vx: 22.0148; vy: -0.972006; s: 533.619; d: 5.81523; speed: 49.3612; yaw: 357.472
 car id: 0; x: 1386.372; y: 1177.998; vx: 11.47191; vy: -1.09597; s: 611.8177; d: 5.975918
 car id: 1; x: 1231.255; y: 1188.678; vx: 19.85036; vy: 0.5660669; s: 455.4512; d: 5.964447
 car id: 2; x: 1331.163; y: 1179.437; vx: 14.59147; vy: -1.752163; s: 556.8674; d: 9.849002
 car id: 3; x: 1334.08; y: 1183.157; vx: 16.74993; vy: -2.117211; s: 559.3532; d: 5.828172
 car id: 4; x: 1171.071; y: 1186.214; vx: 18.521; vy: 0.950447; s: 395.136; d: 5.915824
 car id: 5; x: 1123.594; y: 1182.968; vx: 19.54905; vy: 1.685188; s: 347.0682; d: 5.639203
 car id: 6; x: 1307.579; y: 1189.969; vx: 14.785; vy: -0.906174; s: 532.2606; d: 1.999554
 car id: 7; x: 1413.027; y: 1174.996; vx: 17.89758; vy: -2.282388; s: 638.8436; d: 5.861498
 car id: 8; x: 1339.305; y: 1186.543; vx: 14.80836; vy: -1.903387; s: 564.1705; d: 1.88304
 car id: 9; x: 1210.888; y: 1191.924; vx: 20.75338; vy: 0.9145503; s: 435.2047; d: 2.032931
 car id: 10; x: 1228.281; y: 1184.574; vx: 21.03316; vy: 0.6924005; s: 452.3401; d: 9.965472
 car id: 11; x: 1307.781; y: 1181.852; vx: 14.7648; vy: -1.167523; s: 533.3622; d: 10.04417

Process finished with exit code 9
 *
 */
