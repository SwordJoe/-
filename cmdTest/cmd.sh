cd ../build
path=`pwd` 
echo $path

cmake .. -DENABLE_TEST=true  -DCMAKE_BUILD_TYPE=Debug #-DYUV420SP_REVERSE=1
make
cd -
cp $path/test/bin/simcv_test ./test
#cp ./test ./ffmpeg_pic_test
