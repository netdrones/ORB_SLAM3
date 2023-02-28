echo "Configuring and building Thirdparty/DBoW2 ..."

cd Thirdparty/DBoW2
cmake -Bbuild build -GNinja -DCMAKE_BUILD_TYPE=Release
cmake --build build --target install

cd ../g2o

echo "Configuring and building Thirdparty/g2o ..."

cmake -Bbuild build -GNinja -DCMAKE_BUILD_TYPE=Release
cmake --build build --target install

cd ../Sophus

echo "Configuring and building Thirdparty/Sophus ..."

cmake -Bbuild build -GNinja -DCMAKE_BUILD_TYPE=Release
cmake --build build --target install

cd ../../

echo "Uncompress vocabulary ..."

cd Vocabulary
tar -xf ORBvoc.txt.tar.gz
cd ..

echo "Configuring and building ORB_SLAM3 ..."

cmake -Bbuild build -GNinja -DCMAKE_BUILD_TYPE=Release
cmake --build build --target install
