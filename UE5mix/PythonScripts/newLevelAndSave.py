import unreal
levelTools = unreal.Level
editorLevelLibrary = unreal.EditorLevelLibrary
levelSubSys = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
#levelTools = unreal.level

#innit new level
newLevel = "myNewLevel"

#create new level
myNewLevel = levelSubSys.new_level("/Game/Levels/newLevel")

#set level as current level
levelSubSys.set_current_level_by_name(newLevel)

#save level
levelSubSys.save_current_level()
