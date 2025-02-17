import gymnasium as gym
import ns3ai_gym_env
import os
import time

from stable_baselines3 import PPO
from stable_baselines3.common.callbacks import BaseCallback
from stable_baselines3.common.logger import TensorBoardOutputFormat
from stable_baselines3.common.logger import configure
from stable_baselines3.common.monitor import Monitor


class mycb(BaseCallback):
    def __init__(self, check_freq: int, save_dir: str, verbose: int = 0):
        super().__init__(verbose)
        self.check_freq = check_freq
        self.save_dir = save_dir

    def _init_callback(self):
        if self.save_dir is not None:
            os.makedirs(self.save_dir, exist_ok=True)

    def _on_step(self) -> bool:
        for i in self.locals:
            self.model.save(self.save_dir)

save_dir = "/home/saves/save_final3"
log_dir = "/home/logs/run_final3"

if not os.path.exists(save_dir):
    os.makedirs(save_dir)

if not os.path.exists(log_dir):
    os.makedirs(log_dir)

target = "rl-handover-example"
ns3Path = "/ns-3-dev"
env = gym.make("ns3ai_gym_env/Ns3-v0", targetName=target, ns3Path=ns3Path)
env = Monitor(env, log_dir, allow_early_resets=False)

# env.reset()


model = PPO("MlpPolicy", env, verbose=1, learning_rate=0.0001, n_steps=512, batch_size=64)

# callback = mycb(check_freq=50_000, save_dir="./saves/PPO_novo")

# model.learn(total_timesteps=300_000, tb_log_name="PPO_novo", callback=callback)

#model.load(f"/home/saves/save_trigger_un3/model_217600.zip")
 
steps=512
i=1
print("Starting")
while True:
    i += 1
    model.learn(total_timesteps=steps,
                reset_num_timesteps=False, log_interval=100, progress_bar=False)
    if i % 50 == 0:
        while not os.path.exists(f"{save_dir}/model_{steps*i}.zip"):
            model.save(f"{save_dir}/model_{steps*i}.zip")
            print('here')

# episodes = 10
#
# for ep in range(episodes):
#     obs = env.reset()
#     done = False
#     terminated = False
#     while not terminated:
#         obs, reward, terminated, truncated, info = env.step(env.action_space.sample())
#         print(obs, reward)
#         print("Reward: ", reward, "Terminated: ", terminated, "Truncated: ", truncated, "Info: ", info)

# env.close()
