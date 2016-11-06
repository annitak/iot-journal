IOT-Journal is created as a part of the UCLA Fall 2016 Engineering 96C class on IOT (Internet of Things). The project is intended for the UCLA Depression Grand Challenges and aims to provide more data to people with depression as well as mental health professionals. By creating a journaling device, we hope to help patients and mental health professionals monitor symptoms of depression. IOT-Journal uses machine learning to recognize symptoms of depression and track changes in symptoms over time. Patients can easily communicate with the device by speaking to it and answering prompts. Mental health professionals and patients can then download the data easily and quickly either from the device or through a secure cloud platform.

Getting Started on Linux: https://cloud.google.com/sdk/docs/quickstart-linux

Google Cloud SDK Setup
----------------------
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
  * $ export GOOGLE_APPLICATION_CREDENTIALS=<path_to_service_account_file>
  * $ gcloud auth activate-service-account --key-file=service-account-file
  * $ gcloud auth print-access-token
3. Copy and paste access_token into curl_request_access_token.sh
4. chmod +x curl_request_access_token.sh
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


TO DO: Extract returned text from GCloud Speech Recognition. Analyze for sentiment and mental health measures.
