import json

with open("recording.json") as json_file:
    json_data = json.load(json_file)
result = json_data['results']
result_len = len(result)
journal_alternatives_list = []
for i in range(0, result_len):
	alternative = result[i]
	alt1 = alternative['alternatives']
	alt2 = alt1[0]
	tr = alt2['transcript']
	journal_alternatives_list.append(tr)

journal_entry = ''.join(journal_alternatives_list)
print(journal_entry)