"""Python: ใส่เนื้อหาเริ่มต้นลงตาราง site_content ใน Supabase
ใช้: SUPABASE_URL=... SUPABASE_SERVICE_KEY=... python tools/seed_content.py
(service key ใช้ในเครื่องเท่านั้น ห้ามใส่ในเว็บหรือ commit ขึ้น GitHub)"""
import json, os, urllib.request

url = os.environ["SUPABASE_URL"].rstrip("/")
key = os.environ["SUPABASE_SERVICE_KEY"]
rows = [
    {"key": "hero_th", "value": "การเดินทางไม่มีวันสิ้นสุด หากพวกคุณไม่ยอมแพ้"},
    {"key": "hero_en", "value": "The Journey Never Ends. If You Guys Don't Give Up"},
    {"key": "bio", "value": "ผู้ก่อตั้งโปรเจกต์ Minecraft Roleplay LuminaEther Official ชอบสร้างสิ่งที่ไม่เคยมีมาก่อน ทั้งแอดออน โมเดล และเว็บไซต์"},
]
req = urllib.request.Request(
    f"{url}/rest/v1/site_content?on_conflict=key",
    data=json.dumps(rows).encode(),
    headers={"apikey": key, "Authorization": f"Bearer {key}",
             "Content-Type": "application/json",
             "Prefer": "resolution=merge-duplicates"},
    method="POST",
)
print("seeded", urllib.request.urlopen(req).status)
