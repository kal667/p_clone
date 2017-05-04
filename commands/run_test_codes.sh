#!/bin/sh

# Run this script from xys/obj$:

# set path
setenv PATH /afs/glue/class/old/enee/759c/llvm/llvm-3.4-install/opt/bin/:$PATH

# create byte code
clang -c -emit-llvm ../test_codes/example0.c -o ../test_codes/example0.bc

clang -c -emit-llvm ../test_codes/example1.c -o ../test_codes/example1.bc

clang -c -emit-llvm ../test_codes/example2.c -o ../test_codes/example2.bc

clang -c -emit-llvm ../test_codes/example3.c -o ../test_codes/example3.bc

clang -c -emit-llvm ../test_codes/example4.c -o ../test_codes/example4.bc

# run pass on byte code
opt -load ../opt/lib/libP_clone.so -p_clone ../test_codes/example0.bc -o ../output_test_codes/example.0p_clone.bc

opt -load ../opt/lib/libP_clone.so -p_clone ../test_codes/example1.bc -o ../output_test_codes/example.1p_clone.bc

opt -load ../opt/lib/libP_clone.so -p_clone ../test_codes/example2.bc -o ../output_test_codes/example.2p_clone.bc

opt -load ../opt/lib/libP_clone.so -p_clone ../test_codes/example3.bc -o ../output_test_codes/example.3p_clone.bc

opt -load ../opt/lib/libP_clone.so -p_clone ../test_codes/example4.bc -o ../output_test_codes/example.4p_clone.bc

# pass byte code to human readable IR
llvm-dis ../output_test_codes/example.0p_clone.bc -o ../output_test_codes/example.0p_clone.ll

llvm-dis ../output_test_codes/example.1p_clone.bc -o ../output_test_codes/example.1p_clone.ll

llvm-dis ../output_test_codes/example.2p_clone.bc -o ../output_test_codes/example.2p_clone.ll

llvm-dis ../output_test_codes/example.3p_clone.bc -o ../output_test_codes/example.3p_clone.ll

llvm-dis ../output_test_codes/example.4p_clone.bc -o ../output_test_codes/example.4p_clone.ll