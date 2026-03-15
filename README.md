# ns3-oran-customizable-db

Simulation is an essential part of developing applications for the control and diagnosis of a Radio Access Network (RAN). Evaluating proposed solutions in a realistic simulated scenario is imperative to avoid potential implementation failures. The objective of this work is to add features to the 'ns3-oran' extension of the 'ns-3' network simulator. The implemented features give users the freedom to utilize the extension without restrictions on what data can be sent to the Near-RT RIC. The ability to collect, store, and analyze various types of data is fundamental in developing and deploying machine learning-based solutions. Consequently, the developed tools enable the creation of simulation scenarios capable of training reinforcement learning models using performance metrics that the simulator previously could not handle.

# Dependencies

The dependencies for ns-3 and the ns3-oran and ns3-ai extensions can be installed using the `apt-get` package manager with the following command:
```shell
apt-get update
apt-get install git build-essential libboost-all-dev pybind11-dev cmake sqlite sqlite3 libsqlite3-dev protobuf-compiler python3 python3-pip doxygen sphinx
```

# Installation

## Local Installation
### ns-3 Installation

```shell
git clone [https://gitlab.com/nsnam/ns-3-dev.git](https://gitlab.com/nsnam/ns-3-dev.git)
cd ns-3-dev
git checkout -b ns-3.40 ns-3.40
```

### ns3-oran-customizable-db Installation

In the "ns-3-dev" folder:
```shell
git clone [https://github.com/felip-t/ns3-oran](https://github.com/felip-t/ns3-oran) contrib/oran
```

### ns3-ai Installation (optional, used in one example)
A Python virtual environment is recommended for installing ns3-ai.
In the "ns-3-dev" folder:
```shell
git clone [https://github.com/felip-T/ns3-ai](https://github.com/felip-T/ns3-ai) contrib/ai
./ns3 configure --enable-examples
./ns3
pip install stable_baselines3 gymnasium
pip install -e contrib/ai/python_utils
pip install -e contrib/ai/model/gym-interface/py
```

### Compiling ns-3
In the "ns-3-dev" folder:
```shell
./ns3 configure --enable-examples
./ns3
```

## Dockerfile
Optionally, the tool can be used via the Dockerfile provided in the "docker" directory.
```shell
git clone [https://github.com/felip-T/ns3-oran](https://github.com/felip-T/ns3-oran)
cd ns3-oran/docker
docker build -t ns3-oran-customizable-db .
```

Using the container:
```shell
docker run -it --rm ns3-oran-customizable-db:latest
./setupDocker.sh
```
The last commands will initialize the container, compile ns-3, and install the optional dependencies required to run the second example.

# Experiments

## simple-db-example

To execute, simply run:
```shell
./ns3 run "simple-db-example"
```

This example creates a simulation scenario with a custom report that periodically reports the IPv4 address of a user equipment (UE). The program prints the SQLite queries made to the database to the screen, where it is possible to see the dynamic creation of the `UeIpv4` table, similar to what is highlighted in the article. A more detailed explanation of this example is available in the Sphinx documentation.

The expected execution time is on the order of a few seconds.

## sinr-handover

The second example demonstrates how custom reports can be used to control the nodes in the RAN. This example consists of two eNBs initialized at a distance of 1500 meters apart. A single UE is initialized near one eNB and moves towards the other at a constant speed of 50 m/s. This UE periodically sends the standard location report and a custom SINR report to the Near-RT RIC. There is a custom logic module running in the Near-RT RIC that triggers a handover command whenever a SINR report below a threshold is received. To avoid the handover command from being triggered multiple times before the handover is finalized, a timeout of 2 seconds is set between two consecutive handover commands.

## rl-handover

This example trains a reinforcement learning model for handover management. A full training run until convergence takes a long time. However, it is possible to run the experiment to verify its basic functionality. The experiment is executed via a Python script, which trains a reinforcement learning model using PPO and initializes a simulation scenario multiple times in sequence, collecting observations and taking control actions within the scenario.

A script was created to facilitate the execution of the experiment; this script must be located in the ns-3 root folder. The experiment can be run with:
```shell
cp ./contrib/oran/run-rl-handover-example.sh ./
./run-rl-handover-example.sh
```

**Note:** For installations using the Docker container, the script has already been copied to the root folder, so it only needs to be executed with:
```shell
./run-rl-handover-example.sh
```

All observations received by the model, as well as its reward and the action taken, are displayed on the screen. 
The example runs until it is interrupted by the user (Ctrl+C).

More information about the example, as well as an illustration of the simulated scenario, are available in the Sphinx documentation.

# LICENSE

This repository builds upon software provided by NIST, which has its own license. License details are available in the `LICENSE.md` file.

# Documentation

## Doxygen
The documentation for the implemented features can be generated using Doxygen:
```shell
cd contrib/oran/doc
doxygen
```
The code above will generate a folder named "html". The `index.html` file can be opened in a web browser to access the documentation.

## Sphinx
Information regarding the additions made has been included in the ns3-oran manual.
The manual can be compiled with:
```shell
cd contrib/oran/doc
make html
```
The code above will generate the documentation in "contrib/oran/doc/build/html". The documentation can be accessed by opening the `index.html` file from that folder in a web browser.
