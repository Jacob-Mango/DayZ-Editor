class EditorHelpDialog: EditorDialogBase
{
	void EditorHelpDialog(string title)
	{
		AddContent(new MessageBoxPrefab("DayZ Editor support is handled through our Discord!\nClick 'Discord' to join and report bugs / ask questions\nFeedback is always much appreciated!"));
		
		AddButton("Discord", "OpenDiscord");
		AddButton("Close", DialogResult.OK);
	}
	
	void OpenDiscord()
	{
		GetGame().OpenURL("discord.com/invite/5g742yH");
	}
}