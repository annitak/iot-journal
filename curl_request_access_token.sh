#!/bin/bash

# Must be in the same directory as service_account_file.json
export GOOGLE_APPLICATION_CREDENTIALS=service_account_file.json
gcloud auth activate-service-account --key-file=service_account_file.json
ACCESSTOKEN=`gcloud auth print-access-token`


curl -s -k -H "Content-Type: application/json" \
     -H "Authorization: Bearer $ACCESSTOKEN" \
     https://speech.googleapis.com/v1beta1/speech:syncrecognize \
         -d @sync-request.json \

# Records, processes, and transcribes journal entry to journal.txt
python recorder.py
echo "Recording completed. Transcribing..."
python transcribe.py recording.raw > recording.json
python process_recording.py
