## What is this?

- This is a custom world generator for minecraft bedrock!

### Contributing
Thanks for considering to do that!
1. To do this just goto the TODO.md
2. Pick a thing to work on
3. Clone the branch of code you want to work with
4. Once you have made your changes just create a pull request and i will have a look

### Compiling
To compile the plugin a few things are needed:
- A copy of Visual Studio 2022
- The lastest version of Liteloader that this plugin supports (at the time of writing this is version 1.20.0.01)
- Before opening the VS2022 project run the update_sdk.cmd
- Then open the VS2022 project
- Before you build you need to go the the properties of the LLPIW Project and change the post build steps <br />
```xcopy /Y /S "$(TargetDir)*.*" "E:\Projects\DevEnvys\BedrockEditionServer\plugins\"``` <br />
to <br />
```xcopy /Y /S "$(TargetDir)*.* "DIR OF YOUR LITELOADER PLUGINS FOLDER"```
- Click build and it should all work!
