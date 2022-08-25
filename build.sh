echo "## Build Dependencies (rtPerfLog)"
cd rtPerfLog
rm -r build
mkdir build
cd build
cmake ..
cmake --build .
cd ../..

echo "## Build performance test"
mkdir build
cd build
cmake ..
cmake --build . --target performance-none32 
cmake --build . --target performance-an32 
cmake --build . --target performance-onecmp32
cmake --build . --target performance-twocmp32
cmake --build . --target performance-res32
cmake --build . --target performance-none64
cmake --build . --target performance-an64 
cmake --build . --target performance-onecmp64
cmake --build . --target performance-twocmp64
cmake --build . --target performance-res64

echo "## Build validation test"
cmake .. -DVAL_TIME=True 
cmake  --build . --target val-mul 
cmake  --build . --target val-mul-enc 


echo "## Build fault sim and metrics test"
cmake --build . --target detcap

cd ..