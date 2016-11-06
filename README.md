Getting Started on Linux: https://cloud.google.com/sdk/docs/quickstart-linux

Google Cloud SDK Setup
----------------------
1. Extract Google Cloud SDK
   $ tar xzvf google-cloud-sdk-133.0.0-linux-x86_64.tar.gz
2. Add Cloud SDK Tools to Path
   $ ./google-cloud-sdk/install.sh
   * When prompted, set the rc file to: /etc/profile
3. Initialize and Login
   $ gcloud init

   
REST API Speech Recognition Tutorial: https://cloud.google.com/speech/docs/rest-tutorial#make_a_non-streaming_rest_api_recognize_request
------------------------------------
1. Download transcribe.py, sync-request.json, and audio.raw
2. Follow steps for authenticating: https://cloud.google.com/speech/docs/common/auth#authenticating_with_application_default_credentials
   $ export GOOGLE_APPLICATION_CREDENTIALS=<path_to_service_account_file>
   $ gcloud auth activate-service-account --key-file=service-account-file
   $ gcloud auth print-access-token
3. Copy and paste access_token into curl_request_access_token.sh
4. chmod +x curl_request_access_token.sh
   $ ./curl_request_access_token.sh
5. Run
   $ export GCLOUD_PROJECT=your-project-id
   $ python transcribe.py audio.raw
