// Copyright 2016-2018 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifdef _WIN32
#include <windows.h>
#endif

// interface to token pool
struct TokenPool {
  virtual ~TokenPool() {}

  virtual bool Acquire() = 0;
  virtual void Reserve() = 0;
  virtual void Release() = 0;
  virtual void Clear() = 0;

  // returns false if token pool setup failed
  virtual bool SetupClient(bool ignore, bool verbose,
                           double& max_load_average) = 0;
  virtual bool SetupMaster(bool verbose,
                           int parallelism,
                           double max_load_average,
                           const char* style) = 0;

#ifdef _WIN32
  virtual void WaitForTokenAvailability(HANDLE ioport) = 0;
  // returns true if a token has become available
  // key is result from GetQueuedCompletionStatus()
  virtual bool TokenIsAvailable(ULONG_PTR key) = 0;
#else
  virtual int GetMonitorFd() = 0;
#endif

  // returns NULL if token pool is not available
  static TokenPool* Get();
};
