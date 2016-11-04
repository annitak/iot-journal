curl -s -k -H "Content-Type: application/json" \
     -H "Authorization: Bearer access_token" \
     https://speech.googleapis.com/v1beta1/speech:syncrecognize \
         -d @sync-request.json
