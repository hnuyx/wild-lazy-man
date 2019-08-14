
import requests
import time

baseurl = "http://faucet.ropsten.be:3001/donate/"

kv = {
      'accept': 'application/json',
      'accept-encoding': 'gzip, deflate',
      'accept-language': 'en-US,en;q=0.8,zh-CN;q=0.5,zh;q=0.3',
      'connection': 'keep-alive',
      'host': 'faucet.ropsten.be:3001',
      'referer': 'http://faucet.ropsten.be:3001/',
      'user-agent': 'Mozilla/5.0 (Windows NT 6.3; W…) Gecko/20100101 Firefox/61.0'
     }

#accounts = {
#            "0xf6b7fb95618a20b42e1ed29fbc5921d25dad04f5"
#           }

#accounts = {
#        "0xf6b7fb95618a20b42e1ed29fbc5921d25dad04f5",
#        "0x949890cbf57b7cad8b7bb7332002a5f1c491aa9e",
#        "0xba01b48a1ecc4ac189729a706f225b955ad850a1",
#        "0xfccea12d085091a8ca7a24bc09b9db6890572f3d",
#        "0x4dd3dedd8e310fae7c871396729fcadf499e3127",
#        "0x9dc4ecc0ddcf019eeec9a44483426eb0fac073a0",
#        "0x991ed0236bce419b7fba0fc0a51fe577108a3821",
#        "0xac51443e428955138293222197732c5deb86511e",
#        "0x697eb1dbd0e8e03e1651c1aa0a61ecece0223218",
#        "0x60a5fbbef571395e3fd72bf0155e0e99b1b9d162",
#        "0xe14b7a8a99118dce2de2f60fedd5557454f74168",
#        "0x023f818951abdd5c748f8475974fc6cf5980156f",
#        "0xb7be7b369fcd595203a205667844159c9fa06a81",
#        "0xe2be8041aff1ab0b0f219ecc57269354211e4e0d",
#        "0x8a20dfcbd0bbf9edb0cd0eaf144847344fb188a2",
#        "0xf78b332bb0b5c682d485b9bce3780f6ea42ef9d1",
#        "0xeed320d920f0f3a1b1ad40cb8bf49985980b54d5",
#        "0x87599792a94e0205ceff6546bd1fbe2b815f47db",
#        "0x3c0c1e625f6b5bcfe0f317c259b54d18aadab871",
#        "0x8f4e50016aff75484ab4bf006f201f3bd0a8d65b",
#        "0xa426494b29695d9cb7e368cdac560b413c7551b1",
#        "0xeb7eb283bccf2aee3dddad6a9fd4aecafb7e6914",
#        "0x5bc2d93c4016cd2df02986c2923ff3b6298bc3c5",
#        "0x2f40d5aa9604b1c2f1fef67fc0cc31feba2588b0",
#        "0x249a6bf059a9d3775db911b3ab4969c0f5f42d65",
#        "0xb352ca6278e2f15181abe5d0f995dc5d76f919e7",
#        "0x21f71e63e8eaad68b398dc0b089f6a51a765f624",
#        "0xc1746fbe5c4a65338648bfc493a62432a251b498",
#        "0x015f5a9122d58bc6e903eb9b7e23e53bb2cbfd68",
#        "0x09903bf88aec780f154545ffe82ede0c05d020bc",
#        "0x15e528ff812f2bafb7b2a930cb74166a0a624a02",
#        "0x2af4b4bde63f9c93a4d3ba38c9ed8214c2c808b2",
#        "0x01d187dfabf19cd818305fd8429d42f783490926",
#        "0x2cab1c7d0a35148320692fe14d149711cba67ab5",
#        "0x4c917522cf4acef4580b8e352f932bdb56bc9697",
#        "0x71fb537fcbb91bacb0dcb91680218ca8d8ab9df9",
#        "0x35ceb132eeac40fa6b2790e5350a4082ae660fd4",
#        "0xf355c0b262055a0a5b121cf08d33ad1df5e0c40a",
#        "0x616f6b5503eda7779b7adca62171bb3b081201a6",
#        "0xcc489e9cb4153aa0e57c290b32871187befda7c0",
#        "0x366984a6572f19e180bcbe80b574c5cf5ea26d14",
#        "0x2f23ba0448d38d15f41659b8735f66f96cb63847",
#        "0x4a35d0b70edbb1d31c47e38c89ddd43e447d41dd",
#        "0xf952f25ee163d515d543b80576c75828c7750e66",
#        "0x247910004b6866e649b7a5cc04449852a96f89b2",
#        "0xa88b833bd790d070eb6db49774681eee211e2e32",
#        "0xc6969e12b5b6ca74ed85f32615f4c6cf916fe895",
#        "0x7bbbbe0d29346c6e7a44f6ab0c3318a6952acb0b",
#        "0x22b23ae856740c35ca7cb9960b0bb2f8e6630173",
#        "0x32c4d123a84e084ecf26669c92d885dc46ba5527",
#        "0xbc2cb93ea2b628aa2da492f3f342842f5e368911",
#        "0xeeeda965a7af44e1b87b53dfe1a83f8e49fd1d4d",
#        "0xbfc8c65aef37cbdb8e1f931bf5befb76c418387f",
#        "0xefb07478c4d626f812b542c5059ea599723f6870",
#        "0x3adb36c4c8e8ebc2a6ef62ab44f870fa58712d87",
#        "0xf12b5fa6830277cce170ba9fe9372c66a6130b0a",
#        "0x760e82845b4b7a390a8b92789d36d3e4e006ac96",
#        "0x9fe27c4197dd0e6856f08297d60316df11982a21",
#        "0x736009f589d3192e9ddb4f515e0bc3758d7e0925",
#        "0xfa53e822fc82b249fa99169bf0ae4d88a83c2106",
#        "0x84558c3b5a96e341794051b17445185bed0e6f34",
#        "0x228cb039c41926174f5d6771bf6a48f861fa2236",
#        "0x6fc91439a38461034b8a26cd2beb77b804d8ab46",
#        "0x2fb090cc69643d91f3b40a24a76a587fda64db67",
#        "0x39b8e981c5d83f500d3344ad8cb6949e0acf0dd6",
#        "0xbafb96acdacbbe2d6206b83b985f995b84da19d3",
#        "0xe7a50f5a694ed62f1506feb0a6eff96f5b51d3e2",
#        "0x85705f10bc0b11a339e5d4209a47f1b0a8b349c7",
#        "0xa0f9042b6a8edae70b95d247afcc9543a0e1ce72",
#        "0xd6f63fc2ea20793332fabf2e02c551d770097333",
#        "0x7968ebffa12687a54682d3950beda6c166b6a993",
#        "0x4082eee23ab01d62c1dcfd49cb5a6a3d9b3dd361",
#        "0x194bad607d727a0056b24bc50be4a16c85383a68",
#        "0xb9d55da1506e50877c21fbce1f5dd617ca37e30f",
#        "0xec19aa41fa1092e416bd14194e266a4c8e48cdaf",
#        "0xc371523c47ae935b6e55d70c4f1a0d0057657e2b",
#        "0x260101a1b8276833cd941aa6ef2a8a256238631c",
#        "0xc7a72ecf465ae86d402337c12623c5788e07c759",
#        "0x5a4fe58cff097ae84251e4a55a7a532afc3e873d",
#        "0x696ef03776089c90d88bf287dbb1b565c3b1386c",
#        "0x09afe6c9f2e308ee5b9eecafed4520982c75b983",
#        "0xfc16b3186453375acce29992c888b3d78a5edd49",
#        "0xfac377174bb46b6bd50d758878e91e34c44a25f7",
#        "0x7720dd7ab79cd8aa737957254d6e7e5cec48ea80",
#        "0xb0174b48ec72faaeb3a6bb6a1498553166948625",
#        "0x85dfdc19f7859c41a6509b948f2625cbc614a0f1",
#        "0x97f36de3e7b703f05711c48564dbf5f68e46ca2a",
#        "0xc28c00c83eb592e40aa88b0317d14ba57f431a0f",
#        "0x437aeb0962b7732f8c804268500bbf7a2d14f610",
#        "0xa949b237baff348ab0ca41a3c8f5de42b3ae22f2",
#        "0x7e3b99afb834213f08842306a1dc9252a1c242b0",
#        "0x18f1afd0793cc6c05c6bf51abe799b6c588a04e5",
#        "0xe45573589d5f4836e86fe058f2b6addb6eeacdc3",
#        "0xc382b2b7e6eaabd4e1bb654070567c041da98711",
#        "0x426d9de1bafca79f0bb8007e3db689660fbb68da",
#        "0x096b20288f04c717c027814a6b48c4685993a1eb",
#        "0x8fdb346fe5ec40cdad614286e5e03dbc0379ac68",
#        "0x78969c6e84f52111e684b378b8fba09675f5ede8",
#        "0x1a43ac1665afdaa3220665f2b242752c33730883",
#        "0x4af1d48adc91ae1b771b3bd08804b35c17cc0ebc",
#        "0x505b6b331714179692cc7f8c9fc996108ae475d8"
#        }

try:
    for acc in accounts:
        url = baseurl + acc
        print(url)
        r = requests.get(url, params = kv)
        print(r.status_code)
        r.raise_for_status()
        time.sleep(10)
except:
    print("failed")
