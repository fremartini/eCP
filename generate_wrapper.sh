cd eCP/eCP
python3 file_combine.py --files eCP.cpp distance.cpp pre-processing.cpp query-processing.cpp --out combined.cpp
python3 file_combine.py --files data_structure.hpp eCP.hpp pre-processing.hpp query-processing.hpp --out combined.hpp
cd ..
cd ..
rm -rf __pycache__
rm _eCP_wrapper.cpython-36m-x86_64-linux-gnu.so
rm eCP_wrapper.py
rm -rf wrapper/build
rm wrapper/combined.cpp
rm wrapper/combined.hpp
rm wrapper/eCP.i
rm wrapper/eCP_wrap.cxx
mv eCP/eCP/combined.cpp wrapper
mv eCP/eCP/combined.hpp wrapper/
cd wrapper
python3 interface_gen.py --file combined.cpp
swig -c++ -python eCP.i
python3 setup.py build_ext --inplace
cd ..
mv wrapper/_eCP_wrapper.cpython-36m-x86_64-linux-gnu.so ./
mv wrapper/eCP_wrapper.py ./
