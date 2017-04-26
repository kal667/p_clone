 // Global Variable Declarations

 
 GlobalVariable* gvar_int32_g = new GlobalVariable(/*Module=*/*mod,
 /*Type=*/IntegerType::get(mod->getContext(), 32),
 /*isConstant=*/false,
 /*Linkage=*/GlobalValue::CommonLinkage,
 /*Initializer=*/0, // has initializer, specified below
 /*Name=*/"g");
 gvar_int32_g->setAlignment(4);

 GlobalVariable* gvar_int32_z = new GlobalVariable(/*Module=*/*mod,
 /*Type=*/IntegerType::get(mod->getContext(), 32),
 /*isConstant=*/false,
 /*Linkage=*/GlobalValue::CommonLinkage,
 /*Initializer=*/0, // has initializer, specified below
 /*Name=*/"z");
 gvar_int32_z->setAlignment(4);

 GlobalVariable* gvar_array__str = new GlobalVariable(/*Module=*/*mod,
 /*Type=*/ArrayTy_1,
 /*isConstant=*/true,
 /*Linkage=*/GlobalValue::PrivateLinkage,
 /*Initializer=*/0, // has initializer, specified below
 /*Name=*/".str");
 gvar_array__str->setAlignment(1);

 // Global Variable Definitions
 gvar_int32_g->setInitializer(const_int32_7);
 gvar_int32_z->setInitializer(const_int32_7);
 gvar_array__str->setInitializer(const_array_8);