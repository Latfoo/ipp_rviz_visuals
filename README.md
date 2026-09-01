# ipp_rviz_visuals

Publishes RViz markers for the BlueROV and the water tank. Used by `simulation.launch.py` and `experiment.launch.py` in the `ipp` package.

## Node

`robot_marker_publisher` (`src/robot_marker_publisher.cpp`) publishes `visualization_msgs/Marker` on the `robot_marker` topic.

1. `bluerov` marker, the BlueROV mesh. Moves with the pose received on `vision_pose_cov`.
2. `tank` marker, the water tank mesh. Published once per second at a fixed pose.

Both meshes come from the `hippo_sim` package (`package://hippo_sim/models/...`). RViz needs `hippo_sim` installed to show them.
