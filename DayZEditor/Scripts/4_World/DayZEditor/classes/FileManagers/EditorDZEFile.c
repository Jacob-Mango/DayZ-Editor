class EditorDZEFile: EditorFileType
{
	override EditorSaveData Import(string file, ImportSettings settings)
	{
		EditorSaveData save_data = new EditorSaveData();
		
		if (!FileExist(file)) {
			EditorLog.Error("File not found %1", file);
			return save_data;
		}
		
		// Temporary fix, Binarize always = 0
		//JsonFileLoader<EditorSaveData>.JsonLoadFile(file, save_data);
		EditorJsonLoader<EditorSaveData>.LoadFromFile(file, save_data);
		
		// bugfix to fix the id not incrementing
		EditorSaveData bug_fix_save_data = new EditorSaveData();
		foreach (EditorObjectData object_data: save_data.EditorObjects) {
			
			if (GetGame().GetModelName(object_data.Type) != "UNKNOWN_P3D_FILE") {
				bug_fix_save_data.EditorObjects.Insert(EditorObjectData.Create(object_data.Type, object_data.Position, object_data.Orientation, object_data.ScaleVector, object_data.Flags));
			} else {
				EditorLog.Warning("Ignoring %1 on import. Invalid type, possible for crash", object_data.Type);
			}
		}
			
		foreach (int id: save_data.DeletedObjects) {
			bug_fix_save_data.DeletedObjects.Insert(id);
		}
				
		bug_fix_save_data.MapName = save_data.MapName;
		bug_fix_save_data.CameraPosition = save_data.CameraPosition;
		
		return bug_fix_save_data;
		
		/*
		FileSerializer file_serializer = new FileSerializer();
		if (!file_serializer.Open(file, FileMode.READ)) {
			EditorLog.Error("File in use %1", file);
			return save_data;
		}
		
		if (!file_serializer.Read(save_data)) {
			file_serializer.Close();
			EditorLog.Error("Unknown File Error %1", file);
			return save_data;
		}
		
		file_serializer.Close();*/
	}
	
	override void Export(EditorSaveData data, string file, ExportSettings settings)
	{
		if (FileExist(file) && !DeleteFile(file)) {
			return;
		}

		// Temporary fix, Binarize always = 0
		//JsonFileLoader<EditorSaveData>.JsonSaveFile(file, data);
		EditorJsonLoader<EditorSaveData>.SaveToFile(file, data);
		return;
		
				
		FileSerializer file_serializer = new FileSerializer();
		if (!file_serializer.Open(file, FileMode.WRITE)) {
			return;
		}
		
		if (!file_serializer.Write(data)) {
			file_serializer.Close();
			return;
		}
		
		file_serializer.Close();
	}
	
	override string GetExtension() {
		return ".dze";
	}
}