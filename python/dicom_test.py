import pydicom
import os

dcm_dir = 'c://dicom_test'
out_dir = 'c://dicom_test//anon'

if not os.path.exists(out_dir):
    os.makedirs(out_dir)

for dcm_file in os.listdir(dcm_dir):
    if dcm_file.lower().endswith('.dcm'):
        print(dcm_file)
        dcm_path = os.path.join(dcm_dir, dcm_file)
        out_path = os.path.join(out_dir, dcm_file)
        ds = pydicom.dcmread(dcm_path)
        ds.PatientName = 'testname'
        ds.PatientID = 'testname'
        ds.remove_private_tags()
        ds.save_as(out_path)