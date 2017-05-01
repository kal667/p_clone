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
#include "llvm/IR/BasicBlock.h"

using namespace llvm;


namespace {
struct P_clone :  public ModulePass
{

        /** Constructor. */
	static char ID;                           
	P_clone() : ModulePass(ID) {}

        //DEFINE_INTPASS_ANALYSIS_ADJUSTMENT(PointerAnalysisPass);

        /*
        *
        *
        *
        */
        // TODO:Change to module pass and then iterate over functions
        // This will allow us to only create one global variable
        virtual bool runOnModule(Module &M) {
            bool modified = false;
            
            // Create new global variable
            Type *I32Ty = Type::getInt32Ty(M.getContext());
            errs() << "Created Function Type: ";
            errs() << I32Ty << " ";
            errs() << *I32Ty << "\n";
            
            // Global Variable Declarations
             GlobalVariable* gvar_int32_g = new GlobalVariable(/*Module=*/M,
            /*Type=*/I32Ty,
            /*isConstant=*/false,
            /*Linkage=*/GlobalValue::CommonLinkage,
            /*Initializer=*/0, // has initializer, specified below
            /*Name=*/"g");
            gvar_int32_g->setAlignment(4);

            // Global Variable Definitions
            // TODO: initialize this value
            //gvar_int32_g->setInitializer(I32Ty);

            for(Module::iterator F = M.begin(), E = M.end(); F!=E; ++F) {
                errs() << "In function: ";
                errs() << F->getName() << "\n";

                for (Function::iterator b = F->begin(), be = F->end(); b != be; ++b) {
                    for (BasicBlock::iterator i = b->begin(), ie = b->end(); i != ie; ++i) {
                        errs() << *i << "\n";
                        
                        // Checks for function call
                        if (CallInst* callInst = dyn_cast<CallInst>(&*i)) {
                            errs() << "Found function\n";
                            Function *func = callInst->getCalledFunction();
                                
                            // Checks against NULL
                            if (func) {
                                StringRef func_name = func->getName();
                                errs() << "Function name: " ;
                                errs() << func_name.str() << "\n";

                                // Function must start with 'p'
                                if (func_name.front() == 'p'){
                                    errs() << "Function name starts with 'p'\n";

                                    // Prevent recursive calls to pop_direct_branch
                                    if (!(func_name.str() == "pop_direct_branch")) {
                                    
                                        // Given by Amir
                                        if (!func->isDeclaration()) {
                                            
                                            // Clone the function
                                            ValueToValueMapTy VMap;
                                            Function *cloned_func = CloneFunction(func, VMap, false, NULL);
                                            if (cloned_func == NULL) {
                                                errs() << "ERROR: Cloning failed!\n";
                                                return modified;
                                            }
                                            else {
                                                errs() << "Function cloned\n";
                                                //Going to modify so change return value
                                                modified = true;
                                            }
                                            
                                            // Iterate through instructions OF CLONED FUNCTION looking for return instruction
                                            for (Function::iterator b2 = cloned_func->begin(), be2 = cloned_func->end(); b2 != be2; ++b2) {
                                                for (BasicBlock::iterator i2 = b2->begin(), ie2 = b2->end(); i2 != ie2; ++i2) {
                                                    if (ReturnInst *temp_ret_inst = dyn_cast<ReturnInst>(&*i2)) {
                                                        errs() << "Found return instruction: ";
                                                        errs() << *temp_ret_inst << "\n";

                                                        // This gets the type of the original function
                                                        Type *func_return_type = func->getReturnType();
                                                        errs() << "Function return type: ";
                                                        errs() << func_return_type << " ";
                                                        errs() << *func_return_type << "\n";
                                                        
                                                        // Check to see if the function returns an int
                                                        if (func_return_type == I32Ty) {
                                                            errs() << "Function returns type int\n";

                                                            // Create a new StoreInst and LoadInst
                                                            //
                                                            //StoreInst: global variable stores return value IN CLONED FUNCTION
                                                            Value *ret_value = temp_ret_inst->getReturnValue();
                                                            errs() << "Return value: " ;
                                                            errs() << *ret_value << "\n";
                                                            StoreInst *global_store_inst = new StoreInst(ret_value, gvar_int32_g, false);
                                                            // Insert store instruction before return
                                                            i2->getParent()->getInstList().insert(i2, global_store_inst);

                                                            // TODO:
                                                            // LoadInst: call variable loads global AT CALL SITE, after call
                                                            // LoadInst *global_load_inst = new LoadInst(,,);
                                                        }

                                                        // Add a call to pop_direct_branch() before return instruction IN CLONED FUNCTION
                                                        Function* func_pop_direct_branch = M.getFunction("pop_direct_branch");
                                                        CallInst* void_36 = CallInst::Create(func_pop_direct_branch, "", i2);
                                                        void_36->setCallingConv(CallingConv::C);
                                                        void_36->setTailCall(false);
                                                        AttributeSet void_36_PAL;
                                                        void_36->setAttributes(void_36_PAL);
                                                    }
                                                }
                                            }

                                            // Given by Amir
                                            // Replace called function with cloned function AT CALL SITE
                                            func->getParent()->getFunctionList().push_back(cloned_func); //will push the cloned function to the list of functions in current module
                                            cloned_func->setLinkage(GlobalValue::InternalLinkage); //will the set the linkage of cloned function to internal linkage
                                            callInst->setCalledFunction(cloned_func); // will change the called function of initial call instruction
                                        }
                                    }

                                    // Notify that it's a pop_direct_branch call
                                    else {
                                        errs() << "But it's a pop_direct_branch\n";
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
            }
        return modified;
    }
};
}

char P_clone::ID = 0;
static RegisterPass<P_clone> X("p_clone", "P-Function Clone Pass", false, false);
