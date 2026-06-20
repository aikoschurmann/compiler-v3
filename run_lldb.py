import lldb
debugger = lldb.SBDebugger.Create()
debugger.SetAsync(False)
target = debugger.CreateTarget("./out/test_runner")
process = target.LaunchSimple(["std_mem_clone"], None, None)
for thread in process:
    for frame in thread:
        print(frame)
