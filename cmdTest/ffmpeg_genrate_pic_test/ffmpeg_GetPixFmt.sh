ffmpeg -i "lena.jpg" -pix_fmt rgb24 pixfmt/ffmpeg_rgb24_256x256.rgb
#ffmpeg -i "lena.jpg" -pix_fmt bgr24 ffmpeg_bgr24_256x256.bgr
ffmpeg -i "lena.jpg" -pix_fmt yuv420p pixfmt/ffmpeg_yuv420p_256x256.yuv
ffmpeg -i "lena.jpg" -pix_fmt nv12 pixfmt/ffmpeg_nv12_256x256.yuv
ffmpeg -i "lena.jpg" -pix_fmt nv21 pixfmt/ffmpeg_nv21_256x256.yuv

# files=`ls $folder`
# for file in $files:
#     echo $file
#     str1=${file#*_}
#     pixfmt=${str1%++}
#     echo $pixfmt

./test imwrite pixfmt/ffmpeg_rgb24_256x256.rgb rgb24 256 256 outputJpg/rgb24_output.jpg
#./test convert ffmpeg_rgb24_256x256.rgb rgb24 256 256 rgb24_output.jpg
./test imwrite pixfmt/ffmpeg_yuv420p_256x256.yuv yuv420p 256 256 outputJpg/yuv420p_output.jpg
./test imwrite pixfmt/ffmpeg_nv12_256x256.yuv nv12 256 256 outputJpg/nv12_output.jpg
./test imwrite pixfmt/ffmpeg_nv21_256x256.yuv nv21 256 256 outputJpg/nv21_output.jpg

