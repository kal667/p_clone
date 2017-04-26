//===- Hello.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "Hello World" pass described
// in docs/WritingAnLLVMPass.html
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "hello"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/InstIterator.h"

using namespace llvm;



namespace {
struct P_clone :  public FunctionPass
{

        /** Constructor. */
	static char ID;                           
	P_clone() : FunctionPass(ID) {}

        //DEFINE_INTPASS_ANALYSIS_ADJUSTMENT(PointerAnalysisPass);

        /**
         * @brief Runs this pass on the given function.
         * @param [in,out] func The function to analyze
         * @return true if the function was modified; false otherwise
        */
        virtual bool runOnFunction(Function &F){
            for (Function::iterator bb = F.begin(), bbe = F.end(); bb != bbe; ++bb) {
                BasicBlock &b = *bb;
                for (BasicBlock::iterator i = b.begin(), ie = b.end(); i != ie; ++i) {
                    if (isa<CallInst>(i)) {
                        StringRef name = cast<CallInst>(i).getCalledFunction().getName();
                        char first_letter = name.front();
                        if (first_letter == 'p'){
                            errs() << "P_clone: ";
                            errs() << "function needs to be cloned\n";
                        }
                        else {
                            errs() << "Hello: " ;
                            errs() << "skip function\n";
                        }
                    }
                }
            }
            return false;
        }
};
}

char P_clone::ID = 0;
static RegisterPass<P_clone> X("p_clone", "P-Function Clone Pass", false, false);



