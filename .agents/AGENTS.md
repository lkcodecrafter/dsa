# Workspace Rules

## Code and Explanation Preferences
- **Simplification**: Always simplify the implementation by removing redundant constructs (such as using a distance array directly instead of separate visited arrays and level-by-level loop structures in BFS).
- **Inline Comments**: Include descriptive inline comments in the code explaining each critical logical step.
- **Dry Run in Comments**: Always include a step-by-step Dry Run in the file's comments showing states of variables, data structures, and outputs.
- **Visualizations**: For structures like graphs, draw ASCII representations of nodes and edges in the comments to help visualize the topology.
- **Memorization/Recall Scenarios**: Provide simple examples or scenarios in the comments that help recall/memorize key concepts of the algorithm or code structure.
- **1-Minute Quick Revision in File**: Add a section in the file comments for a "1-Minute Quick Revision" to easily review core logic and rules.
- **1-Minute Quick Review in Chat**: Present a clean, bulleted 1-minute quick review note in the chat summary.
- **Comment-Only Explanations**: Avoid putting long conceptual or code walkthrough explanations in the chat. Write them directly as code comments in the file, keeping the chat response short and pointing the user to the code.
- **Detailed Functor & STL Mechanics**: For custom comparators (e.g., for `std::priority_queue`), include a commented block explaining functor instantiation, how the container internally calls `operator()`, and how the boolean return value determines heap priority (e.g., bubble-down behavior when returning `true`).
- **Line-by-Line Execution Traces**: For complex algorithms (e.g., monotonic stack, DP, tree traversals), include inline step-by-step traces for the first few steps/iterations showing exact variable values, stack/queue states, and condition evaluations.
