//===------------------------- p_clone.cpp  --------------------------------===//
//
//          ENEE645 - Project
//          Kyle Kelly & Greg Coard        
// 
//
//===----------------------------------------------------------------------===//


#define DEBUG_TYPE "hello"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/GlobalVariable.h"

using namespace llvm;



namespace {
struct P_clone :  public FunctionPass
{

        /** Constructor. */
	static char ID;                           
	P_clone() : FunctionPass(ID) {}

        //DEFINE_INTPASS_ANALYSIS_ADJUSTMENT(PointerAnalysisPass);

        /*
        *
        *
        *
        */
        virtual bool runOnFunction(Function &F){
            
            // Create new global variable
            Module *M = F.getParent();
            Type *I32Ty = Type::getInt32Ty(F.getContext());
            errs() << "Created Function Type: ";
            errs() << I32Ty << " ";
            errs() << *I32Ty << "\n";
            // Global Variable Declarations
             GlobalVariable* gvar_int32_g = new GlobalVariable(/*Module=*/*M,
            /*Type=*/I32Ty,
            /*isConstant=*/false,
            /*Linkage=*/GlobalValue::CommonLinkage,
            /*Initializer=*/0, // has initializer, specified below
            /*Name=*/"g");
            gvar_int32_g->setAlignment(4);

            for (Function::iterator b = F.begin(), be = F.end(); b != be; ++b) {
                for (BasicBlock::iterator i = b->begin(), ie = b->end(); i != ie; ++i) {
                    errs() << *i << "\n";
                    
                    // Checks for function call
                    if (CallInst* callInst = dyn_cast<CallInst>(&*i)) {
                        errs() << "Found function\n";
                        Function *func = callInst->getCalledFunction();
                            
                        // Checks against null
                        if (func) {
                            StringRef func_name = func->getName();
                            errs() << "Function name: " ;
                            errs() << func_name << "\n";
                            
                            // Function must start with 'p'
                            if (func_name.front() == 'p'){
                                errs() << "Function name starts with 'p'\n";
                                
                                // Given by Amir
                                if (!func->isDeclaration()) {
                                    
                                    // Clone the function
                                    ValueToValueMapTy VMap;
                                    Function *cloned_func = CloneFunction(func, VMap, false);
                                    if (cloned_func == NULL) {
                                        errs() << "ERROR: Cloning failed!\n";
                                    }

                                    // This gets the type of the original function
                                    Type *func_return_type = func->getReturnType();
                                    errs() << "Function Type: ";
                                    errs() << func_return_type << " ";
                                    errs() << *func_return_type << "\n";
                                    
                                    // Check to see if the function returns an int
                                    if (func_return_type == I32Ty) {
                                        errs() << "Function returns type int\n";
                                    }
                                }
                            }
                        }
                        // Null case
                        else {
                            errs() << "Indirect call\n";
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
