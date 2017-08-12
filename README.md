# ATLAS Arm - EMG Prosthetic Hand
The ATLAS (Articulating Tactile Limb Amputation Supplement) Arm is a 3D Printable, muscle-controlled prosthetic hand that can be manufactured for under $250 in consumable materials.

The ATLAS Arm started as an [IDEA Grant](http://ugradresearch.uconn.edu/idea/) project at the University of Connecticut by [Stephen Hawes](http://www.stephenhawes.com). Stephen documented the first six versions of the hand in a YouTube [video series](https://www.youtube.com/playlist?list=PLIeJXmcg1baLB6wgaJ4MkH0-Whnp8Us2D).

## Instructions
------
The ATLAS Arm was designed to be completely customizable for any mid-forearm amputee to use. Only a few tools are necessary to create one at home, and about $250 in materials, all listed in the Bill of Materials document.

1. Using the Advancer Technologies EMG sensor, test sensor pad locations using the test.ino script in the CAD folder in the Github Repo. Description of how this is done is a comment at the top of the test.ino file. Once you've found the ideal locations, mark the Reference, End, and Middle of the muscle with R, E, and M respectively. Do so with a fine-point Sharpie in small text.

2. Using Skanect and the Kinect sensor, take a 3D scan of the remaining forearm of the amputee for which the arm is being made. Take two scans: One with a 90 degree bend at the elbow, and another with the forearm straight. Save as an .obj file.

3. Take 8 measurements of the amputee's remaining hand using millimeters as a unit. These measurements are as follows:
  - P1 - distance from the rotational center of the third knuckle to the rotational center of the second knuckle on the index finger.
  - Px - Width of the palm (from base of index finger to base of pinky).
  - Py - Length of the palm (from wrist to third knuckle).
  - Pz - Thickness of the palm.
  - Wx - Width of wrist (in direction of thumb to pinky).
  - Wz - Thickness of wrist.
  - Ff - Full length of forearm (from wrist to rotational center of the elbow).
  - Fa - Length of remaining forearm (from end of amputation to rotational center of the elbow.)

4. Load the "Atlas Arm" Fusion 360 file. Save your own copy of the file to your Autodesk cloud and rename it to the name of the amputee, or some other distinguishable title. Then, edit the new file in the following ways:
  1. Under the "Modify" menu, select "Change Parameters" option with the sigma icon.
  2. Enter in your new values for Px, Py, Pz, P1, Wx, and Wz.
  3. If the model fails to render, it is possible that the design does not scale properly for the dimensions given. The timeline at the bottom can be rolled back to see where the error occurred, and fixed.

5. Export the following components as separate STL files: 1, 2, 3, 4, 5, 1joints, 2joints, 3joints, 4joints, 5joint, palm, and palmJoints. This can be done by clicking on the component in the list on the left, then clicking "3D Print" in the "Make" menu.

6. 3D print the fingers and the palm. Each print requires dual extrusion with the second nozzle extruding Ninjaflex. Print files 1 and 1joints together, 2 and 2joints together, etc. with the joints file being printed in Ninjaflex and the other part printed in ABS. It is recommended to use a Lulzbot Taz with a FlexyDually Extruder.

7. 3D print the Base Unit. This can be exported in the same fashion as the fingers from Fusion 360. Print in PLA plastic.

8. 3D print the socket component. The socket should be printed in Ninjaflex, and the outer shell printed in ABS plastic, using a dual extrusion printer. It is recommended to use a Lulzbot Taz with a Flexydually Extruder.

9. Assemble the hand.
    a. Insert M4 heat-set inserts into the back of each finger using a soldering iron until the insert is completely clear of the slot for the Ninjaflex joint.
    b. Slide each finger onto their respective Ninjaflex joints and secure the fingers using an M4x10mm machine screw and a M4 washer. You will have to puncture the Ninjaflex joint before attempting to screw through it.
    c. String up each finger. Cut five lengths of fishing line one foot long, and feed them from the tip of each finger into the motor cavity in the back of the palm. Tie off the fishing line at the tip of each finger with a loose knot, but do not cut off the excess.
    d. Solder the leads of the motor to the appropriate pins on the motor driver board, and glue the spool onto the spindle of the motor using CA glue. Glue the ends of the five lengths of fishing line to the inside of the spool. After drying, wrap the cabling once more around the spool and fit the motor into it's cavity.
    e. Loosen the knots at the ends of the fingers, and tighten each one so that each finger is slightly bent forward and under tension. Glue the knots secure with CA glue and trim the excess.
    f. Wire the necessary pins from the motor driver to the pinout at the base of the palm, then glue the pinout into place.

10. Make the Core Module. Follow the schematic in the "Hardware" folder using parts from the Bill of Materials. Print the enclosure and cap for the Core Module found in the "CAD" folder. Use the CAD model in Fusion 360 as reference.

11. Edit firmware. A few example firmware files are provided. If the device will only be using the standard ATLAS Arm prosthetic hand attachment, then "firmwareHandOnly.ino" can be used as is.

12.
