//! TODO: remove this controller and directly connect with EditorObject
//! (maybe add a NotifyPropertyChanged to EditorObject to handle once things get changed?)
//! This would be another step closer to removing EditorObjectData since Scale, Position, and Orientation would 
//! become public variables, with a Notify once things get changed? (Along with SetPosition methods etc..)
class EditorObjectPropertiesDialogController: DialogBaseController
{
	string name;
	vector position;
	vector orientation;
	float scale;
	
	bool show;
	bool static_object;
	bool locked;
	
	bool bounding_box;
	bool world_marker;
	bool map_marker;
	bool list_item;
	
	protected EditorObject m_EditorObject;
	
	void SetEditorObject(EditorObject editor_object)
	{
		m_EditorObject = editor_object;
		
		name = m_EditorObject.GetDisplayName();
		position = m_EditorObject.GetPosition();
		orientation = m_EditorObject.GetOrientation();
	}
	
	override void PropertyChanged(string property_name)
	{
		switch (property_name) {
			
			case "name": {
				m_EditorObject.SetDisplayName(name);
				break;
			}
			
			case "position": {				
				m_EditorObject.SetPosition(position);
				break;
			}			
			
			case "orientation": {				
				m_EditorObject.SetOrientation(orientation);
				break;
			}
			
			case "scale": {
				m_EditorObject.SetScale(scale);
				break;
			}
						
			case "show": {
				m_EditorObject.Show(show);
				break;
			}
			
			case "static_object": {
				m_EditorObject.SetStaticObject(static_object);
				break;
			}
			
			case "locked": {
				m_EditorObject.SetLocked(locked);
				break;
			}
			
			case "bounding_box": {
				m_EditorObject.EnableBoundingBox(bounding_box);
				break;
			}	
					
			case "world_marker": {
				m_EditorObject.EnableObjectMarker(world_marker);
				break;
			}	
							
			case "map_marker": {
				m_EditorObject.EnableMapMarker(map_marker);
				break;
			}
			
			case "list_item": {
				m_EditorObject.EnableListItem(list_item);
				break;
			}
		}
	}
}


// Stores state of the Collapse data
class EditorObjectPropertiesDialogState
{
	static bool GeneralGroup = true;
	static bool ObjectGroup = true;
	static bool FlagsGroup = true;
}

class EditorObjectPropertiesDialog: EditorDialogBase
{
	protected EditorObjectPropertiesDialogController m_EditorObjectPropertiesDialogController;
	
	protected ref GroupPrefab m_GeneralGroup;
	protected ref GroupPrefab m_ObjectGroup;
	protected ref GroupPrefab m_FlagsGroup;
	
	protected EditorObject m_EditorObject;
	
	void EditorObjectPropertiesDialog(string title, EditorObject editor_object)
	{		
		m_EditorObjectPropertiesDialogController = EditorObjectPropertiesDialogController.Cast(GetController());
		m_EditorObjectPropertiesDialogController.SetEditorObject(editor_object);
		
		m_EditorObject = editor_object;
	
		m_GeneralGroup = new GroupPrefab("General", m_Controller, string.Empty);
		m_GeneralGroup.Insert(new CheckBoxPrefab("Show", m_Controller, "show", editor_object.IsVisible()));
		m_GeneralGroup.Insert(new EditBoxPrefab("Name", m_EditorObject, "Name", editor_object.GetDisplayName()));
		m_GeneralGroup.Insert(new VectorPrefab("Position", m_EditorObject, "Position", editor_object.GetPosition()));
		m_GeneralGroup.Insert(new VectorPrefab("Orientation", m_EditorObject, "Orientation", editor_object.GetOrientation()));
		m_GeneralGroup.Insert(new EditBoxNumberPrefab("Scale", m_EditorObject, "scale", editor_object.GetScale().ToString(), 0.01));
		m_GeneralGroup.Open(EditorObjectPropertiesDialogState.GeneralGroup);
		
		m_ObjectGroup = new GroupPrefab("Object Settings", m_Controller, string.Empty);
		m_ObjectGroup.Insert(new CheckBoxPrefab("Lock", m_Controller, "locked", editor_object.IsLocked()));
		m_ObjectGroup.Insert(new CheckBoxPrefab("Static Object", m_Controller, "static_object", editor_object.IsStaticObject()));
		m_ObjectGroup.Open(EditorObjectPropertiesDialogState.ObjectGroup);
		
		m_FlagsGroup = new GroupPrefab("Object Flags", m_Controller, string.Empty);
		m_FlagsGroup.Insert(new CheckBoxPrefab("Bounding Box", m_Controller, "bounding_box", editor_object.BoundingBoxEnabled()));
		m_FlagsGroup.Insert(new CheckBoxPrefab("World Marker", m_Controller, "world_marker", editor_object.ObjectMarkerEnabled()));
		m_FlagsGroup.Insert(new CheckBoxPrefab("Map Marker", m_Controller, "map_marker", editor_object.MapMarkerEnabled()));
		m_FlagsGroup.Insert(new CheckBoxPrefab("List Item", m_Controller, "list_item", editor_object.ListItemEnabled()));
		m_FlagsGroup.Open(EditorObjectPropertiesDialogState.FlagsGroup);
		
		AddContent(m_GeneralGroup);
		AddContent(m_ObjectGroup);
		AddContent(m_FlagsGroup);
		
		if (editor_object.GetWorldObject().IsMan()) {
			GroupPrefab human_controller = new GroupPrefab("Human Controller", m_Controller, string.Empty);
			human_controller.Insert(new ButtonPrefab("Button1", m_Controller, "button"));
			AddContent(human_controller);
		}
		
		AddButton(DialogResult.OK);
		AddButton(DialogResult.Cancel);
		
		EditorEvents.OnObjectSelected.Insert(OnObjectSelected);
	}
	
	void ~EditorObjectPropertiesDialog()
	{
		EditorObjectPropertiesDialogState.GeneralGroup = m_GeneralGroup.IsOpen();
		EditorObjectPropertiesDialogState.ObjectGroup = m_ObjectGroup.IsOpen();
		EditorObjectPropertiesDialogState.FlagsGroup = m_FlagsGroup.IsOpen();
		
		delete m_GeneralGroup;
		delete m_ObjectGroup;
		delete m_FlagsGroup;
	}
	
	private void OnObjectSelected(Class context, EditorObject editor_object)
	{
		SetEditorObject(editor_object);
	}
	
	void SetEditorObject(EditorObject editor_object)
	{
		m_EditorObject = editor_object;
	}
	
	override typename GetControllerType() {
		return EditorObjectPropertiesDialogController;
	}
}