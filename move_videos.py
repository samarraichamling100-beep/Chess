import os
import shutil
import glob
from datetime import datetime
def move_mp4_files(source_dir, dest_dir):
    # Standardize paths to handle spaces and trailing slashes
    source_dir = os.path.abspath(source_dir)
    dest_dir = os.path.abspath(dest_dir)
    
    # Create the destination folder if it doesn't exist yet
    if not os.path.exists(dest_dir):
        os.makedirs(dest_dir)
        print(f"Created destination folder: {dest_dir}")
        
    # Search for all .mp4 files in the source directory
    search_path = os.path.join(source_dir, "*.mp4")
    mp4_files = glob.glob(search_path)
    
    if not mp4_files:
        print(f"No .mp4 files found in {source_dir}")
        return

    print(f"Found {len(mp4_files)} video(s). Starting transfer...")
    
    for file_path in mp4_files:
        file_name = os.path.basename(file_path)
        target_path = os.path.join(dest_dir, file_name)
        
        # Prevent overwriting if a file with the same name already exists
        if os.path.exists(target_path):
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            name, ext = os.path.splitext(file_name)
            file_name = f"{name}_{timestamp}{ext}"
            target_path = os.path.join(dest_dir, file_name)
        
        try:
            shutil.move(file_path, target_path)
            print(f" Successfully moved: {file_name}")
        except Exception as e:
            print(f"❌ Failed to move {file_name}. Error: {e}")

if __name__ == "__main__":
    # --- CONFIGURE YOUR PATHS HERE ---
    # Replace these paths with your actual Windows/Mac/Linux folders
    # Note: Use double backslashes (\\) or forward slashes (/) on Windows
    SOURCE_FOLDER = r"C:\Users\hp\Downloads" 
    DESTINATION_FOLDER = r"C:\Users\hp\Videos\ChessProject"
    
    move_mp4_files(SOURCE_FOLDER, DESTINATION_FOLDER)
