# CSMA-Simulator-UI
This simulates a CSMA with UI/UX elements made in QT creator and C++
The histogram is created by going to file open and it will be created at runtime.
The histogram is the sorted list of each node and the message that has taken place when you run the simulation.

# Carrier-Sense Multiple Access
CSMA is MAC protocol where there is a series of nodes that verify traffic before transmitting the shared transmission amoung other nodes.

Carrier length with change the length of each carrier that transports messages node to node
Message length will change the specific messages length inside of nodes that are sent to carriers.
Probability will change the conditional probability that a node will encounter a collision
Carrier Busy Delay is the time a node waits when a collision takes place.
Tick Total is the amount of runs that take place to be placed in their individual positions in the Histograms

# QT Creator UI
The UI is created using QT code and C++. Each attribute of the simulation uses a variety of widgets.
They are placed and sorted by having the histogram as the central widget and having the attribute widgets in individual docks
