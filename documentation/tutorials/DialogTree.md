# Structure of `DialogTree` in YAML

## Basic Example

```yaml
- name: my_node_321
  speaker: yuki
  pages:
    - We must find the ancient artifact before they do.
    - The key lies within the forgotten tomb.
    - Something seems fishy. Stay vigilant.
  options:
    - text: Agreed. Let's gather more information discreetly.
      type: go_to_node
      data: { target_node_name: my_dialog_node_567 }
    - text: I have a bad feeling too. We must proceed cautiously.
      type: node
      data:
        speaker: yuki
        pages:
          - Agreed. Trusting our instincts is crucial in these situations.
          - Let's carefully analyze each step and keep an eye out for any hidden dangers.
        options:
          - text: Agreed. Let's gather more information discreetly.
            type: exit_dialog
    - text: I'll keep my eyes open and watch our backs
      type: exit_dialog
    speaker: charlie
- name: my_node_567
  pages:
    - The ancient artifact before they do lies within the forgotten tomb.
  options:
    - text: Let's do it!
      type: exit_dialog
```

## Overview

The structure of the YAML format consists of several key components. Let's break it down:

- *`speaker`*: This field represents the speaker of the dialog node. In the example, it is set as "yuki," indicating that Yuki is the speaker for this particular dialog node.
- *`pages`*: This field represents the pages or lines of dialog spoken by the speaker. It is a sequence of strings, where each string represents a separate line of dialog. In the example, there are three pages of dialog for Yuki.
- *`options`*: This field represents the available dialog options or responses for the player. It is a sequence of options, where each option contains text, type, and data. The *`text`* field represents the text displayed to the player for that option, the *`type`* field indicates the type of action associated with the option (e.g., "go_to_node" or "exit_dialog"), and the `data` field provides additional data specific to the option type.

In the example you provided, there are three options for the player to choose from. The first option is of type "go_to_node" and includes a `target_node_name` indicating the name of the next dialog node to navigate to. The second option is of type "node" and includes a nested dialog node structure with its own speaker, pages, and options. The third option is of type "exit_dialog," indicating that selecting it will exit the current dialog.

This structure allows for flexible and branching dialog paths within your game, providing various dialog options and allowing navigation between different dialog nodes.


