﻿
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

accounts = {
"0x8f4e50016aff75484ab4bf006f201f3bd0a8d65b",
"0xc6969e12b5b6ca74ed85f32615f4c6cf916fe895",
"0xf12b5fa6830277cce170ba9fe9372c66a6130b0a",
"0xc28c00c83eb592e40aa88b0317d14ba57f431a0f",
"0xce9ec7373ddb37b8e9ecd436386877e618e48a45",
"0x970ec418233b04ffb4e1ada98417b103e14982c3",
"0xe0ca33e3c0bb90d3d69984634e5356773c4f2009",
"0xe80959b2302068b8b9f5636067c6644622f8e39b",
"0x144308154db000d88db0bcb28eb6b23add3ac81e",
"0x8fcdd3728c47ef36a853e39a0a333ec5b6c775e5",
"0xa1683c2466c09b5f038b2a5b73d7531dfcd16d87",
"0x2a9134bf104ed316306386be744e67148f2cf740",
"0x26d565c855a3ff508bae01b7871074953a4f42df",
"0xbc52c01e699c1edf78cc2e6c2c27f7d932b506bd",
"0x8cc6311e09602eba539f59e7ffe7f938e93eaea9",
"0x4a291742c90b5c99f3915f2a866c38eed7bd4ad6",
"0x132fc54010ddf2c94c22b0df4c9e61369645f75a",
"0xec25208e2978f91e9d17bacc0140a8a33fa3628c",
"0x6c1e0b9bb49a8d5e5b7f1782328e815c8089087b",
"0x43d6568ca2de7b154ba6a9f72950c1ae7eb247e4",
"0x315838ee936a7e62968882bcdde9dc3bec5e68db",
"0xfc635c843c3b051591c2ca875f714262eadc56d6",
"0xd68c99cb42fd9982e0f3f859569b1dbf920f1aae",
"0xbeda1ead74576b5622df832955742901dd03b785",
"0xad2eadb70b573e9b3669513fb1202e5474da9839",
"0x9d7a3238e6fd8345968069d4efec3c4594778db3",
"0x16f21575a297f941a25e6a17b0bfcf43993dd4dc",
"0xe53a3770e9f1b1f64a6cf68d2c8dfe9bc09f9b04",
"0x0a9dbbfd956d1aa81743697dc564387cccb278ab",
"0xb01dbbe601e88fa7ce33b30b9d2c78a814fe480a",
"0x03ae089e3eb52d682b99c31015bd4b7b2bb3d87f",
"0x9d6e67d6b38fd1a11c9f648e0a3896a086fded80",
"0x560a7713e19b4b4ef53f133bb8e5975caac5b9b2",
"0xe6e31a20c341e7f4147442826578ce85d39da890",
"0xd0194d81efb544af82eb0655e419a6020e2ebadc",
"0x1bcec49b55cb25ff4c37f4c405b9a77a83793ef9",
"0xc8603cdd26436512e11e818915a5ee468a7c7f1d",
"0xe310eb955d1f9d9dec1bd241de043f462e4d89c0",
"0x812fab9f9fb0264dac9702b309709fb437dae720",
"0xd17c4f5e22c8a2f979064c187a61df3d502161f6",
"0x20c16dd608accaff28360fd5db7481550603bd65",
"0x78a093c34ec2e7facaa530893f0f0800c7fbeea7",
"0x2025b0fb49675b8f64039d9270c20e5ad21aff74",
"0x0d46b2673d00bc6725d01c387d89c19f955810ad",
"0x9737f607f62a7a4068a7307dd3793d49e2ac4a50",
"0x62643e4ca5fd8e11210e493110e3d39e37c43c31",
"0x4e7bc675a4b1266a884b349584ad9dcd760c05e7",
"0x791183fe4f889d54a3c80f430ab2576530402da8",
"0x335282ce30f2d4ea618966c917f745dad5605cb9",
"0x5667ba273e3bb60823d129d8ebbcc8bc9ca3af4c",
"0xbb8e243148dafcdc281ab8ce3a4ed512ea857a6e",
"0x425c1404180eb781e6c13503f36d36d98e257af6",
"0xc9fb3101b3ddc43c6b129717bfee9a1026f5645d",
"0xed159b3258e0f21fbc50026a32ab10ca23657539",
"0x65aff335bf55b7e82e28516df258e18308a3759f",
"0x00ed9fc2daa1efbaf600f9b7bcd4396e9c702f38",
"0x671e3aacbb1390a9489026a06a2f8fe355b901d9",
"0xde0b067c44d0eab46d039c6ddcf47a4f717fdb73",
"0x5821b6115e2760de4370aeae52f13548297e02eb",
"0x5254bd55e45854962b9e17e6f03d221c3034f46b",
"0x8a258cdcb2bb9c8e12cac59d7b9114cf15c38f96",
"0xab32fa35adac71722b368235f84952f18e8fafd8",
"0xedc584bc7cfca3064d7f0f5df72a4e6994c43c96",
"0x65348494e8d2190c02d5c83bcd7ed952bc1417a8",
"0x59247cce683ae806d75e0af49e3cb75e608e0d2e",
"0xe0eb6e541d5a1b752dccdb2f1a35aedb982c9af6",
"0x8aa20edb20712bb39336652360a9e2244f33a0f1",
"0x899671ea5e8d12051fc170905d669f751a81d909",
"0x4b0b227d842c07c0eb265dcf6ca4d8e7f0e066b6",
"0x67d264ded63d1c183582d305d68d93c83df4180e",
"0xc10b31facabfce0928d29db6baa689ebdd35879b",
"0x1e597f2d1bdedbe97a92b71e42e95af2f43b170a",
"0xd8ffb308acc23b47e158345c601f5e9f6244d7c5",
"0x892673194cad484cc2ddafd7c2e8019094c86b2a",
"0xdd248df62b78d58e8505d630403b3859aceb1ac4",
"0xd4e811a67c2aafa2e777f891b4942223f71cfc52",
"0xa30eb727ccf46dca9b61a20d3d908b957e66b50a",
"0xd26397771ca75aeeec034951afe34201799a7cd2",
"0x853cc3d53e68e3fd0610b352e61f267f0e2622e8",
"0xf7c093f83810539b6902dbfc33448f5b5ab9e031",
"0x05fc0c16f43aaa4a24a3138145728c8b209ba3a9",
"0x1aeb00a1f9571caa79e50b2af643de21e5f611c2",
"0x743a6ff78ef3f945191c088ab2845c651f84cb12",
"0x57676faa58269999eb3b19805266d510bd52d3d4",
"0xd0217dc032aee09e015f3f139c34875e9f59c06d",
"0xf35ed2d2030585d80f46fea60631c9a7c98dbba3",
"0x1dc4b95d2c8546abf8ff7c7274b38a89b79bb43e",
"0xb364bd5970de9c6daa794c24d88e16ff10162c32",
"0x90e06d6e42c76457ebaf23db652de36cb3536b72",
"0x823f736b11c5cec4b2b0e2f3388e7df578e1dd88",
"0xfc98192565b6d7b41e17db275a0ea2da27d489be",
"0xeb42ecbe950b73721cd7e1325ec6609163d4e5a7",
"0xf4ef5dc5587f392e0ad979348572f2de2795d4cb",
"0x894138e9718b05584ba07c2335ce4d6fd02228dc",
"0x25e766e46c86950a8e53bd5599044394d556dc9b",
"0x4115746cbbb4f18eb7bfb0132ef43555f7a38160",
"0x6ecb6ada3e63d45a5b0ed9995744fee148e96808",
"0xf1ba70d98ba84c1d498208b1e5d71386c0d7f9bb",
"0x451946e11892c1953d5a9e0141982f2069732b79",
"0xb12d997ce2035f2505e5fd9e18e88ba3866762ae",
"0x9e371fc308051e939fe8b4e6a27a53b2b42316d8",
"0x8d16741e007b5f09b13f51123cc2b0d252c9715b",
"0xbb5c2a8201e3e47ce9411111164bb445fbd2f88e",
"0x3ebdff247a3ba7954410229445bb3b4a2c678f51",
"0x2152ba9e602a0a9da6a331a45e150a38928d7901",
"0x5cfd081be086873a81b01efd451b0fca9adf919d",
"0xc942cb2b2dbb2414ff20c40d2d9939ae4a0a0660",
"0xd52056e421008e98078502b458c602f1aad0f4e9",
"0x206e5797803a30177ccb4b5f440eaa6df2f06152",
"0x0ec6dbdc1b5d50023248eae3836ceb1024db6e50",
"0x9e0e2b084c8a056acba7859757176c33016dcdef",
"0x181f20c5985266bf142df9ec1540f1fef7692f3a",
"0xaeb812846d1e42ceee04d2b4ffee123ea58ec823",
"0x5ce0a131a8696488ac7b55635f2093fed189b358",
"0xa2f1a642fc6e7a5b6f2724a0cb8820943e562a83",
"0x2e674b4da974fc41dbe99169333e5d210f3920f9",
"0x871d8a053bcf537850c7ba461436ce9c045e7ec7",
"0x6b318bb7b40e91f7787d0f4a890ef43a47257553",
"0x413b23dc4f8679c1563aebc66148b409aba52ac6",
"0xb98084df447d88aaca95027b87750970d2ccdb79",
"0x50c2e3c3ea3783d798626bc95f2bc488c9a96b50",
"0x4a94446897e0bbd0f186d924c5cec2a380963229",
"0xefb81fd559cac18f6508be05e566e69056af8630",
"0x0683c4eb455e7f86662d1a33f9b2b3f5f7673750",
"0x62eefc7e442ada7e1cb0ee118549d209057e47d8",
"0x680e7f4c57724917a10bf1f7d6705bff71e83487",
"0xd4230c5e49b58555045586b84bff75d415b26764",
"0xa7010b03c7d53d4278bb799941fda6c7a88f58a4",
"0x05c6e383f5a655150566b7d436f19e56dc290772",
"0xa7901f538994f99e307b579717bda3e068be5f76",
"0xb388b26314d3a371f84acdc88adffe95c1a2a80e",
"0x7992d774193f338a419fd5c8702fdd20aac13029",
"0xabaae09507be7385e0cc82acfb112ad481f44612",
"0x6a5912f31f29b6a01b5f1b135e36508793230c47",
"0x972abe28dbefeea8e5b17605bbfa26cb95f956af",
"0xa39309e3e04a83f396ee30cc725a6ed0dcbae2cd",
"0x6a000d9ed15f224ccb5502111da7ac6542ac5fa4",
"0x799903f93d3d9e76f625e20882c4571523cebb13",
"0x9a82a28b8d92f6a2a4e3b4a5942d9b6eec36b5ae",
"0x53d5288d8f860ede048cf2eeb119fbafd3aab4d5",
"0x664c68422df2aa47f5eb36c83377e456ef246cb2",
"0xf4a872a31188fb121c781cc469429eec7083e859",
"0xe1ea3b4dcf46d2dea06222505c7f82f4840d56a4",
"0xe605ee997ce3997e8f64405275817ff7de97f847",
"0x476aec9cd72145988f98a108821f0707f9094e4f",
"0xd5563c630d4473ddb27e4804179a53ec27bf56b8",
"0x13e5169dbf13a798d4018114b2a2e5f4efab3989",
"0x6705a70ffe8b93df44e8393d8cb96bac6d2c27b5",
"0x2881d8f7a708d4a94592c1ec1b226c1b77f72117",
"0x6e3e571332950b06175ee11c81bcd18bb9d9e4ad",
"0x08e350ccf0c5a1b57d757eb6c44194a464f7e287",
"0x7fba5214d04d2a2702e528af211e37a9790e38e6",
"0x457e10e11717ebd4f60a8985def9ded56aea28eb",
"0xbffc118600c63b1389c76cb9880365e5e12c2a8e",
"0x18d3c509a0be0b6eceffc5ea7efc57b38417c4e6",
"0xebee826c83f8cef338767cda4df82ee5f97219aa",
"0xd31b82a73b9a9654c22ef29707c6a9c0b46e5483",
"0xe03e2828495d5f290e4ab8e98353d7d2695b2510",
"0x1cd7870cc8b8ccf5dc578b9c9c734508446bf029",
"0x09fa82e176c64abbcd94d43d1b2143202ee93c4d",
"0x6feb2db6ac3081a3c146902f1a1e05e326894631",
"0xd0faaf7da9cc195f19ba3922dfe215c51a283ad1",
"0xece2486f990f8e8480a92707c5dbbfee626c6b40",
"0x45f209d82afa9bc7fb54e53c64ea47b579508601",
"0xf382758e8e5fa4491fc366fc4cbf96509e545e7a",
"0xc85c0cadb5428f7bbca9de45c9a8ce7c8509ac2d",
"0xc32f9b137a0e35034b1927a99258b94babb455e5",
"0x39c5b4a6111a4bffb70d460a4b72e27b17c0d0f8",
"0xaa845a3fc2ba54786f17932a73f7cdea978815ba",
"0x71e49fbc7e236fc5eed8826bb7e308dff9c6d0a1",
"0x219a33accf61501b4534703431991baecdf89a38",
"0xd84c9c7a24be268c33925bd05cb31ff81cb7f325",
"0xde63289e66331938fe07dfd8b3b626943e8056d2",
"0xa9eb2f19b73987110577109278a4fc512e8b6ee2",
"0x1d1833113f81935d5579a124354746be1cf59975",
"0xc402f5feedac47987a8432e9119e7a76df1f7f10",
"0xd199deeb4775c6fc1cb78be1a39642f7a18e4ff1",
"0xac9ae4043291eeb13aa3a29fa17ee37c617218a4",
"0xa4fbafd6d673825f24684e97961389593303b699",
"0x6e03c08edcd01408768f59aadb08148739087a30",
"0x40fb85cca7a4b04326d56342130f52f67105bd8d",
"0x38eba41c69376c1305404396aa163aa0060a94e8",
"0xafd5542c32731c5b978cb422bc395636da05e5a4",
"0xe09ee70f12907ee78356ef6e2619a2b15d6df039",
"0x8e5b687963d496a5d6efd426ac534fc0a2ce02af",
"0xf29dbed00c51ac3adc51392914a57c9dc9366b53",
"0xa2fe98ee47116d8d34724befecd5803f7e3c306b",
"0x3d64a30d435973f68766a893c9cf78073e95be02",
"0xe720ee0e27ae5edfa550cb71cd31d6864975c0ad",
"0xf029438bdefdb490c8370f2e895ae037f93cb689",
"0x5adc7cbff8bb818bd4ef667d4557fb6aa1dad44f",
"0xb4d1f05a10381335a1f5acc749460e3287f7ccb7",
"0x8bbcc4dacd5b074371db3f5ddc71429925f22f4a",
"0x401d41fe7f00e816ec910987fcf71d65063bb787",
"0xa65db3844f8e43748a51b910ff1bce2962e2419e"
}

i = 1

for acc in accounts:
    url = baseurl + acc
    print(i, url)
    r = requests.get(url, params = kv)
    print(r.status_code)
    time.sleep(10)
    i = i + 1
