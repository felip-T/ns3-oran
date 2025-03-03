BASEDIR = "$( cd "$( dirname "$0" )" && pwd )"
./ns3 configure --enable-examples
./ns3
pip install -e contrib/ai/python_utils
pip install -e contrib/ai/model/gym-interface/py
