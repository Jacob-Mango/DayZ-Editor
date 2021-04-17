
// Stores state of the Collapse data
class EditorObjectPropertiesDialogState
{
	static bool GeneralGroup = true;
	static bool Object_Group = true;
	static bool FlagsGroup = true;
}

class EditorObjectPropertiesDialog: EditorDialogBase
{
	
	protected ref GroupPrefab m_GeneralGroup;
	protected ref GroupPrefab m_ObjectGroup;
	protected ref GroupPrefab m_FlagsGroup;
	
	protected EditorObject m_EditorObject;
	
	void EditorObjectPropertiesDialog(string title, EditorObject editor_object)
	{
		SetEditorObject(editor_object);
				
		AddButton(DialogResult.OK);
		AddButton(DialogResult.Cancel);
		
		EditorEvents.OnObjectSelected.Insert(OnObjectSelected);
		EditorEvents.OnObjectDeselected.Insert(OnObjectDeselected);
	}
	
	void ~EditorObjectPropertiesDialog()
	{
		UpdateViewContext();
	}
	
	private void OnObjectSelected(Class context, EditorObject editor_object)
	{
		SetEditorObject(editor_object);
	}
	
	private void OnObjectDeselected(Class context, EditorObject editor_object)
	{
		UpdateViewContext();
	}
	
	
	// Maximum Elegance
	void SetEditorObject(EditorObject editor_object)
	{
		m_EditorObject = editor_object;
		
		UpdateViewContext();
		
		m_GeneralGroup = new GroupPrefab("General", m_EditorObject, string.Empty);
		m_GeneralGroup.Insert(new CheckBoxPrefab("Show", m_EditorObject, "Show"));
		m_GeneralGroup.Insert(new EditBoxPrefab("Name", m_EditorObject, "Name"));
		m_GeneralGroup.Insert(new VectorPrefab("Position", m_EditorObject, "Position"));
		m_GeneralGroup.Insert(new VectorPrefab("Orientation", m_EditorObject, "Orientation"));
		m_GeneralGroup.Insert(new EditBoxNumberPrefab("Scale", m_EditorObject, "Scale", 0.01));
		m_GeneralGroup.Open(EditorObjectPropertiesDialogState.GeneralGroup);
		
		m_ObjectGroup = new GroupPrefab("Object Settings", m_EditorObject, string.Empty);
		m_ObjectGroup.Insert(new CheckBoxPrefab("Lock", m_EditorObject, "Locked"));
		m_ObjectGroup.Insert(new CheckBoxPrefab("Static Object", m_EditorObject, "StaticObject"));
		m_ObjectGroup.Open(EditorObjectPropertiesDialogState.Object_Group);
		
		
		AddContent(m_GeneralGroup);
		AddContent(m_ObjectGroup);
		
		if (editor_object.GetWorldObject().IsMan()) {
			GroupPrefab human_controller = new GroupPrefab("Human Controller", m_EditorObject, string.Empty);
			human_controller.Insert(new ButtonPrefab("Button1", m_EditorObject, "button"));
			AddContent(human_controller);
		}
	}
	
	private void UpdateViewContext()
	{
		EditorObjectPropertiesDialogState.GeneralGroup = m_GeneralGroup.IsOpen();
		EditorObjectPropertiesDialogState.Object_Group = m_ObjectGroup.IsOpen();
		EditorObjectPropertiesDialogState.FlagsGroup = m_FlagsGroup.IsOpen();
		
		delete m_GeneralGroup;
		delete m_ObjectGroup;
		delete m_FlagsGroup;
	}
}