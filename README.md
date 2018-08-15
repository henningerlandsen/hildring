[![Build Status](https://travis-ci.org/henningerlandsen/hildring.svg?branch=master)](https://travis-ci.org/henningerlandsen/hildring)
[![Build status](https://ci.appveyor.com/api/projects/status/g942gs2ugbw5yan6/branch/master?svg=true)](https://ci.appveyor.com/project/henningerlandsen/hildring/branch/master)
[![codecov](https://codecov.io/gh/henningerlandsen/hildring/branch/master/graph/badge.svg)](https://codecov.io/gh/henningerlandsen/hildring)


# hildring
Playground for new ideas, techniques and tools in the form of an OpenGL rendernig engine.

## Todo
- [x] Select a window framework (gflw)
- [x] Setup a rendering window
- [x] Window wrapper
- [ ] Build verification
    - [x] Travis
        - [x] Linux
        - [x] Mac
    - [x] AppVeyor
        - [x] Windows
    - [x] Code coverage
        - [x] Setup codecov.io
        - [x] Generate coverage report
            - [x] Linux
            - [x] Mac os
        - [x] Disable for other platforms?
        - [x] Exclude externals dir
- [x] Setup clang-format
- [x] Testing framework
- [ ] Engine architechture:
    - [ ] Entities
    - [ ] Components
    - [ ] Systems
        - [x] Systems can be registered
        - [x] Constant lookup
        - [x] Use lambda instead of returning pointer

- [ ] GLContext wrapper
- [ ] Capture input events
- [ ] Add scripting framework
