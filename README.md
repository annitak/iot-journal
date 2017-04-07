IOT-Journal is created as a part of the UCLA Fall 2016 Engineering 96C class on IOT (Internet of Things). The project is intended for the UCLA Depression Grand Challenges and aims to provide more data to people with depression as well as mental health professionals. By creating a journaling device, we hope to help patients and mental health professionals monitor symptoms of depression. The ultimate goal of IOT-Journal is to use machine learning to recognize symptoms of depression and track changes in symptoms over time. Patients can easily communicate with the device by speaking to it and answering prompts. Mental health professionals and patients can then download the data easily and quickly either from the device or through a secure cloud platform.

Parts Needed
------------
1. Intel Edison Board with compatible Arduino Breakout Board
2. USB headset with microphone
3. Grove- Starter Kit v3

OS & Requirements
-----------------
1. Install Yocto Embedded Linux OS on the Intel Edison Board prior to beginning this project.
2. Install Python 2.7 or the latest version of Python required by Google Cloud as found in the link below.
3. Connect the parts shown in the Hardware Diagram image file.

Google Cloud SDK Setup
----------------------
Getting Started on Linux Guide: https://cloud.google.com/sdk/docs/quickstart-linux

1. Extract Google Cloud SDK
   * $ tar xzvf google-cloud-sdk-133.0.0-linux-x86_64.tar.gz
2. Add Cloud SDK Tools to Path
   * $ ./google-cloud-sdk/install.sh
   * When prompted, set the rc file to: /etc/profile
3. Initialize and Login
   * $ gcloud init
4. Install the Google APIs Client Library for Python
   * $ pip install --upgrade google-api-python-client

   
REST API Speech Recognition Tutorial: https://cloud.google.com/speech/docs/rest-tutorial#make_a_non-streaming_rest_api_recognize_request
------------------------------------
1. Download transcribe.py, sync-request.json, and audio.raw
2. Follow steps for authenticating: https://cloud.google.com/speech/docs/common/auth#authenticating_with_application_default_credentials
  * $ export GOOGLE_APPLICATION_CREDENTIALS=<service-account-file.json>
  * $ gcloud auth activate-service-account --key-file=<service-account-file.json>
3. Set up Access Token
  * $ gcloud auth print-access-token
  * Copy and paste access_token into curl_request_access_token.sh
  * $ chmod +x curl_request_access_token.sh
  * $ ./curl_request_access_token.sh
5. Run
  * $ export GCLOUD_PROJECT=your-project-id
  * $ python transcribe.py audio.raw


Recording Audio from Microphone
-------------------------------
1. Follow hardware and software set up instructions from "Audio Interface.pdf"
2. To record: $ arecord -f S16_LE -r44100 test.raw
3. To playback: $ aplay test.raw
4. To upload to GCloud and transcribe audio: $ python transcribe.py test.raw


Using JSON from GCloud Speech Recognition
-----------------------------------------
1. Make sure you are in the same directory as your "recording.json" file.
2. Download process_recording.py.



TO DO: Analyze for sentiment and mental health measures.
