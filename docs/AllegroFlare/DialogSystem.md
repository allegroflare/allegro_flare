# DialogSystem



## Spawn a dialog

With an identifier for the dialog node, from anywhere there is an EventEmitter,
call this event emitter method:

```
  - name: emit_activate_dialog_node_by_name_event
    parameters:
      - name: dialog_node_name_to_activate
        type: std::string
        default_argument: '"[unset-dialog_node_name_to_activate]"'
    guards: [ initialized ]
    body: |

```

This will
1) Send a suspend_gameplay message to any Gameplay::Base screen
2) Hijack the controls
3) Create a dialog message 


## Create a listing of all dialog nodes

Do this in `Configurations/Main`


There's also:

```
  - name: build_common_system_dialogs_node_bank
    static: true
    type: AllegroFlare::DialogTree::NodeBank
    body: |
      AllegroFlare::DialogTree::NodeBank node_bank;

      node_bank.add_node(
            "System::INTERNAL::wait_before_exit_program",
            new AllegroFlare::DialogTree::Nodes::Wait(1.0, "System::INTERNAL::exit_program_no_confirm")
         );
      node_bank.add_node("System::INTERNAL::exit_program_no_confirm", new AllegroFlare::DialogTree::Nodes::ExitProgram());
      node_bank.add_node(
            "confirm_exit_program",
            new AllegroFlare::DialogTree::Nodes::MultipageWithOptions
            (
               "system",
               { "Are you sure you want to exit?" },
               { 
                  {
                     "Yes",
                     new AllegroFlare::DialogTree::NodeOptions::GoToNode("System::INTERNAL::wait_before_exit_program"),
                     AllegroFlare::BitFlags<uint32_t>(0)
                  },
                  {
                     "No",
                     new AllegroFlare::DialogTree::NodeOptions::ExitDialog(),
                     // TODO: Add test to ensure this option is focused
                     AllegroFlare::BitFlags<uint32_t>(
                        AllegroFlare::DialogTree::Nodes::MultipageWithOptions::OptionFlags::FLAG_CURSOR_HERE_ON_SPAWN
                     )
                  },
               }
            )
         );

      return node_bank;


    body_dependency_symbols:
     - AllegroFlare::DialogTree::Nodes::MultipageWithOptions
     - AllegroFlare::DialogTree::Nodes::ExitDialog
     - AllegroFlare::DialogTree::Nodes::ExitProgram
     - AllegroFlare::DialogTree::Nodes::Wait
     - AllegroFlare::DialogTree::NodeOptions::GoToNode
     - AllegroFlare::DialogTree::NodeOptions::ExitDialog
```


