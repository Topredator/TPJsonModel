# Copyright (c) 2022 NetEase, Inc. All rights reserved.
# Use of this source code is governed by a MIT license that can be
# found in the LICENSE file.


#!/bin/bash

# set -x

# Const

# target路径地址
project=""
target_name=""
build_configuration="Release"
# 版本号
version=""
zip_flag=false

# Path
root_dir="$( cd "$(dirname "$0")" && pwd )"

target_root="${root_dir}/build"
target_root_dir=${target_root}/${target_name}
temp_iphone_output_dir=${target_root_dir}/build-iphone
temp_iphonesimulator_output_dir=${target_root_dir}/build-iphonesimulator

# 压缩的framework包文件
target_file=

# 打印环境
print_env() {
	echo "----- start build ${target_name} -----"
	echo "target_name=${target_name}"
	echo "build_configuration=${build_configuration}"
	echo "version=${version}"
	echo "root_dir=${root_dir}"
	echo "target_root_dir=${target_root_dir}"
	echo "-----------------------------------------"
}

# 构建环境
setup_env () {
	if [[ -d ${target_root_dir} ]]; then
		echo "删除${target_root_dir}"
		rm -rf ${target_root_dir}
	fi

	if [[ ${target_name} != "" ]] && [[ ${version} != "" ]]; then
			target_file=${target_name}_iOS_v${version}.framework.zip
	fi

	if [[ -d "${target_root}/${target_file}" ]]; then
		echo "删除${target_root}/${target_file}"
		rm -rf ${target_root}/${target_file}
	fi

	mkdir -p $target_root_dir
}

# framework打包
build_framework_release () {

	xcodebuild -configuration ${build_configuration} \
              -project ${project} \
              -target $target_name \
              -sdk "iphonesimulator" \
              ARCHS="x86_64" \
              ONLY_ACTIVE_ARCH=NO\
              CONFIGURATION_BUILD_DIR="${temp_iphonesimulator_output_dir}" \
              BITCODE_GENERATION_MODE=bitcode \
              OTHER_CFLAGS="-fembed-bitcode" \
              build \
              -verbose


  if [[ -f ${temp_iphonesimulator_output_dir}/${target_name}.framework/${target_name} ]]; then
		echo "${target_name} Export ${target_name}.framework Successful!!!"
	else
		echo "${target_name} Export ${target_name}.framework Failed, Exit!!!"
		exit 1
	fi

	xcodebuild -configuration ${build_configuration} \
							-project ${project} \
	   		   		-target $target_name \
	   		   		-sdk iphoneos \
	   		   		ONLY_ACTIVE_ARCH=NO\
			   			CONFIGURATION_BUILD_DIR="${temp_iphone_output_dir}" \
			   			BITCODE_GENERATION_MODE=bitcode \
			   			OTHER_CFLAGS="-fembed-bitcode" \
			   			build \
			   			-verbose

	if [[ -f ${temp_iphone_output_dir}/${target_name}.framework/${target_name} ]]; then
		echo "${target_name} Export ${target_name}.framework Successful!!!"
	else
		echo "${target_name} Export ${target_name}.framework Failed, Exit!!!"
		exit 1
	fi
}

# 导出framework
export_framework () {

	cp -rf ${temp_iphone_output_dir}/${target_name}.framework  ${target_root_dir}/${target_name}.framework

	lipo -create ${temp_iphone_output_dir}/${target_name}.framework/${target_name} \
				 ${temp_iphonesimulator_output_dir}/${target_name}.framework/${target_name} \
				 -output ${target_root_dir}/${target_name}.framework/$target_name

	if [[ -f ${target_root_dir}/${target_name}.framework/$target_name ]]; then
		echo `lipo -info ${target_root_dir}/${target_name}.framework/$target_name`
		echo "${target_name} Export ${target_name}.framework Successful!!!"
	else 
		echo "${target_name} Export ${target_name}.framework Failed, Exit!!!"
		exit 1
	fi

	# Clean
	rm -rf ${temp_iphone_output_dir}
	rm -rf ${temp_iphonesimulator_output_dir}
}


#打包完成功
build_after () {
	if [[ -d ${target_root_dir} ]] && [[ $zip_flag != false ]]; then
		echo "start compress ${target_root_dir} ..."
		cd ${target_root}
		zip -r ${target_root}/${target_file} ${target_name}.framework
	fi
}

function do_show_usage () {
    echo "Usage:"
    echo "  -r: release"
    echo "  -d: debug"
    exit 1
}


## parse options
echo "params: $*"
params=("$@")
for(( i=0;i<${#params[@]};i++)) do
  cur="${params[i]}"
  next="${params[i+1]}"
  echo "cur $cur"
  case $cur in
  --project)
        echo "next $next"
    project="$next"
    ((i++));
    ;;
  -d)
          echo "next $next"
    build_configuration="Debug"
    ;;
  -r)
          echo "next $next"
	build_configuration="Release"
	;;
  --version)
          echo "next $next"
    version="$next"
    ((i++));
    ;;
  --targetName)
          echo "next $next"
		target_name="$next"
		((i++));
		;;
  -z)
          echo "next $next"
		zip_flag=true
		;;
	*) break ;;
  esac
done





echo "开始操作"

if [[ $build_configuration = "Release" ]]; then
	setup_env
	print_env
	build_framework_release
	export_framework
	build_after
else
	echo "${build_configuration}"
	do_show_usage
fi



