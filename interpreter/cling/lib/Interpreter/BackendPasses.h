//------------------------------------------------------------------------------
// CLING - the C++ LLVM-based InterpreterG :)
// author:  Vassil Vassilev <vvasilev@cern.ch>
//
// This file is dual-licensed: you can choose to license it under the University
// of Illinois Open Source License or the GNU Lesser General Public License. See
// LICENSE.TXT for details.
//------------------------------------------------------------------------------

#ifndef CLING_BACKENDPASSES_H
#define CLING_BACKENDPASSES_H

#include <memory>

namespace llvm {
  class Function;
  class LLVMContext;
  class Module;
  class PassManagerBuilder;
  class TargetMachine;

  namespace legacy {
    class FunctionPassManager;
    class PassManager;
  }
}

namespace clang {
  class CodeGenOptions;
  class LangOptions;
  class TargetOptions;
}

namespace cling {
  ///\brief Runs passes on IR. Remove once we can migrate from ModuleBuilder to
  /// what's in clang's CodeGen/BackendUtil.
  class BackendPasses {
    std::unique_ptr<llvm::legacy::PassManager> m_MPM;
    std::unique_ptr<llvm::legacy::FunctionPassManager> m_FPM;

    llvm::TargetMachine& m_TM;
    const clang::CodeGenOptions &m_CGOpts;
    //const clang::TargetOptions &m_TOpts;
    //const clang::LangOptions &m_LOpts;

    void CreatePasses(llvm::Module& M);

  public:
    BackendPasses(const clang::CodeGenOptions &CGOpts,
                  const clang::TargetOptions & /*TOpts*/,
                  const clang::LangOptions & /*LOpts*/,
                  llvm::TargetMachine& TM):
      m_TM(TM),
      m_CGOpts(CGOpts) //,
      //m_TOpts(TOpts),
      //m_LOpts(LOpts)
    {}

    ~BackendPasses();

    void runOnModule(llvm::Module& M);
  };
}

#endif // CLING_BACKENDPASSES_H
