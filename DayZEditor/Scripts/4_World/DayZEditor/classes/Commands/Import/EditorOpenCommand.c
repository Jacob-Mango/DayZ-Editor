class EditorOpenCommand: EditorImportCommandBase
{	
	protected override void Call(Class sender, CommandArgs args) 
	{
		EditorFileDialog file_dialog(GetName(), "*.dze", "", GetDialogButtonName());
		
		string file_name;
		if (file_dialog.ShowDialog(file_name) != DialogResult.OK) {
			return;
		}
		
		OpenFile(file_name);
	}
	
	EditorSaveData OpenFile(string file_name)
	{
		EditorSaveData save_data = ImportFile(file_name, true);
		
		if (save_data) {
			m_Editor.SetSaveFile(file_name);
			m_Editor.GetCamera().SetPosition(save_data.CameraPosition);
		}
		
		return save_data;
	}

	override string GetName() 
	{
		return "#STR_EDITOR_OPEN";
	}

	override string GetIcon() 
	{
		return "set:dayz_editor_gui image:open";
	}
	
	override ShortcutKeys GetShortcut() 
	{
		return { KeyCode.KC_LCONTROL, KeyCode.KC_O };
	}
	
	override typename GetFileType() 
	{
		return EditorDZEFile;
	}
	
	override string GetDialogButtonName() 
	{
		return "#STR_EDITOR_OPEN";
	}
}