# Track Plan: Bug Fix - Avatar Generation Corruption

## Phase 1: Fix and Verify
- [~] Task: Fix `generate_avatars.py` String Formatting
    - [ ] Sub-task: Correct the f-string usage in `to_c_array`.
    - [ ] Sub-task: Verify logic for `image_to_bytes` ensures non-zero data is preserved.
- [x] Task: Regenerate and Verify `avatars.h` bb82f61
    - [ ] Sub-task: Run the script.
    - [ ] Sub-task: Check file content for valid hex values.
- [ ] Task: Conductor - User Manual Verification 'Fix Verification' (Protocol in workflow.md)
