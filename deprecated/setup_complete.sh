echo "installing dependencies"
sudo apt install python3-pip
sudo apt install docker.io
sudo systemctl start docker
sudo systemctl enable docker
cd ..
git clone https://github.com/erikbern/ann-benchmarks/
cd ann-benchmarks
pip3 install -r requirements.txt
cd ..
chmod 777 ./ann-benchmarks -R
cp -r eCP/ann-benchmarks/* ann-benchmarks/
cd ann-benchmarks
echo "building docker images"
sudo python3 install.py
echo "running test on random-xs-20-euclidean"
sudo python3 run.py --algorithm eCP --dataset random-xs-20-euclidean
chmod 777 ./ -R
sudo python3 plot.py --dataset random-xs-20-euclidean

