
#include "math.h"

// ----------------------------------------------------------
// Base Circle data
// ----------------------------------------------------------
constexpr int BASE_NUM_SIDES = 10 ;
constexpr int BASE_NUM_VERTICES = ( BASE_NUM_SIDES * 3 ) ;
constexpr double base_radius = 8.0 ;
constexpr double base_height = 8.0 ;
constexpr float base_angle_step = M_PI * 2.0 / BASE_NUM_SIDES ;

// ----------------------------------------------------------
// Sides data
// ----------------------------------------------------------
constexpr int SIDES_N = 3 ;
constexpr double circle_fraction = 0.3333333 ;
// constexpr double side_fan_angle_step = circle_fraction * 2.0 * M_PI / SIDES_N ;
constexpr double side_curl_angle_step = 2.0 * M_PI / SIDES_N ;
constexpr double radius = 4.0 ;
constexpr double cx = -radius ;
constexpr double cy = 0 ;

// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void display();
 
