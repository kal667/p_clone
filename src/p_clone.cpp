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
#include "llvm/IR/Module.h"
#include "../../test_codes/pop_direct_branch.c"

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
            bool modified = false;
            
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
                                    Function *cloned_func = CloneFunction(func, VMap, false, NULL);
                                    if (cloned_func == NULL) {
                                        errs() << "ERROR: Cloning failed!\n";
                                        return modified;
                                    }

                                    //Given by Amir
                                    func->getParent()->getFunctionList().push_back(cloned_func); //will push the cloned function to the list of functions in current module
                                    cloned_func->setLinkage(GlobalValue::InternalLinkage); //will the set the linkage of cloned function to internal linkage
                                    callInst->setCalledFunction(cloned_func); // will change the called function of initial call instruction
                                    
                                    // Iterate through instructions looking for return instruction
                                    ReturnInst *ret_inst = NULL;
                                    for (Function::iterator b2 = func->begin(), be2 = func->end(); b2 != be2; ++b2) {
                                        for (BasicBlock::iterator i2 = b2->begin(), ie2 = b2->end(); i2 != ie2; ++i2) {
                                            if (ReturnInst *temp_ret_inst = dyn_cast<ReturnInst>(&*i2)) {
                                                errs() << "Found return instruction\n";
                                                errs() << "Return instruction: " ;
                                                errs() << *temp_ret_inst << "\n";
                                                ret_inst = temp_ret_inst;
                                            }
                                        }
                                    }

                                    // Check to see if the function returns an int
                                    // This gets the type of the original function
                                    Type *func_return_type = func->getReturnType();
                                    errs() << "Function Type: ";
                                    errs() << func_return_type << " ";
                                    errs() << *func_return_type << "\n";
                                    
                                    // If so, then we need to create StoreInst
                                    if (func_return_type == I32Ty) {
                                        modified = true;
                                        errs() << "Function returns type int\n";

                                        // Create a new store instruction
                                        // Place return value in global variable
                                        if (ret_inst == NULL) {
                                            errs() << "ERROR: never found return instruction!\n";
                                        }
                                        else {
                                            Value *ret_value = ret_inst->getReturnValue();
                                            errs() << "Return value: " ;
                                            errs() << *ret_value << "\n";
                                            StoreInst *global_ptr = new StoreInst(ret_value, gvar_int32_g, false);
                                        }
                                    }
                                    /*
                                    // Add a call to pop_direct_branch()
                                    CallInst* void_36 = CallInst::Create(pop_direct_branch, "", ret_inst);//This needs to be changed to the return instruction of the clone
                                    void_36->setCallingConv(CallingConv::C);
                                    void_36->setTailCall(false);
                                    AttributeSet void_36_PAL;
                                    void_36->setAttributes(void_36_PAL);
                                    */
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
            return modified;
        }
};
}

char P_clone::ID = 0;
static RegisterPass<P_clone> X("p_clone", "P-Function Clone Pass", false, false);
